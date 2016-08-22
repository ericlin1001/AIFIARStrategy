#ifndef NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_
#define NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_

#include "base.h"
#include "interface.h"
#include "objects.h"
#include "scripting_system.h"
#include "logger.h"

// By Code_B_Silence, NEU China
class StrategyBasis {
 public:
  const GameState & get_gs()const { return gs_; }
  void set_gs(const GameState gs){ gs_ = gs; }
  const BallBasis & get_ball()const { return ball_; }
  inline bool set_ball(const BallBasis ball);
  const RobotBasis & get_robot(int index)const { return robots_[index]; }
  inline bool set_robot(const RobotBasis robot, int index);
  const Object & get_opponent(int index)const { return opponents_[index]; }
  inline bool set_opponent(const RobotBasis opponent, int index);
  const DataDebug & get_debugdata()const { return debugdata_; }
  void set_debugdata(DataDebug debugdata) { debugdata_ = debugdata; }
  const ScriptingSystem & get_filedata()const { return filedata_; }
  const Logger & get_logger()const { return logger_; }

  StrategyBasis(const char *logFile="logger.txt",const char *debugDataFile="debugData.txt",const int t=0);
  virtual ~StrategyBasis() {}

  void Start(const Object objects[]);

protected:
	virtual void PreProcess();
  virtual void DecisionMaking();
  virtual void PostProcess();
 protected:
  enum { ROBOT_NUMBER = 5 };
  
  GameState gs_;
  BallBasis ball_;
  //RobotPID robots_[ROBOT_NUMBER];
  PowerRobot robots_[ROBOT_NUMBER];
  RobotBasis opponents_[ROBOT_NUMBER];

  DataDebug debugdata_;
  ScriptingSystem filedata_;
  Logger logger_;

  //RobotSimple robotPID_;  // For test
  
  // Disallow copy and assign
  StrategyBasis(const StrategyBasis &) {}
  void operator= (const StrategyBasis &) {}
};
 struct MyEnvironment
{ 
	const StrategyBasis*pStrategy;
	MyEnvironment(){
		lastBall.pos.x=-1;
		for(int i=0;i<PLAYERS_PER_SIDE;i++){
			home[i].index=i;
		}
	}
	Robot home[PLAYERS_PER_SIDE];							//我方机器人数组 
	OpponentRobot opponent[PLAYERS_PER_SIDE];				//敌方机器人数组 
	Ball currentBall,										//当前小球的位置 
		lastBall,											//上一次小球的位置 
		predictedBall;										//预计的小球的位置 

	/*Bounds fieldBounds,										//场地范围 
		goalBounds;										//球门的位置与范围 */

	//long gameState;											//当前游戏的状态 
	//long whosBall;											//由谁控制球 
	//void *userData;											//用户自定义信息 
	void update(const StrategyBasis*p){
		pStrategy=p;
		lastBall=currentBall;
		//
		
		for(int i=0;i<PLAYERS_PER_SIDE;i++){
			//
			home[i].pos.x=p->get_robot(i).get_position().GetX();
			home[i].pos.y=p->get_robot(i).get_position().GetY();
			home[i].rotation=p->get_robot(i).get_theta();
			home[i].copyToRobotPID();
			//
			opponent[i].pos.x=p->get_opponent(i).get_position().GetX();
			opponent[i].pos.y=p->get_opponent(i).get_position().GetY();
			opponent[i].rotation=p->get_opponent(i).get_theta();
			opponent[i].copyToRobotBasis();
			if(p->get_gs().matchState!=MatchState::MS_UNDER_WAY){
				home[i].set_vector(0);
				opponent[i].set_vector(0);
				lastBall.pos.x=-1;
			}
		}
		currentBall.pos.x=p->get_ball().get_position().GetX();
		currentBall.pos.y=p->get_ball().get_position().GetY();
		/*currentBall.copyToBallBasis();
		if(p->get_gs().matchState!=MatchState::MS_UNDER_WAY){
			currentBall.set_vector(0);
		}*/
		//whosBall=p->get_gs().ballOwner;
		//
	}
} ;	

#endif  // NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_