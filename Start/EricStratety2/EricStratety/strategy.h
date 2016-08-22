#ifndef NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_
#define NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_

#include "base.h"
#include "objects.h"
#include "logger.h"
#include "GeometryR.h"
#include "area.h"
#include "teamorder.h"
#include "robotrole.h"
class Enviornment_Info;
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 球场上的状态信息 
// 
class BallFieldState 
{ 
public: 
	/** 
	* 球场上的状态信息分析 
	*/ 
	BallFieldState (void); 
	~BallFieldState (void); 

public: 
	/** 
	* 分析球场上的信息，修改记录的球场信息，以便需要者获得 
	*/ 
	void analyse ( Enviornment_Info *);
	void predictBall (Enviornment_Info *); 
	//
	const AreaInfo *getBallArea (void){return ballArea;} 
	BallSpeed getBallSpped (void){ return ballSpeed;} 
	BallDirection getBallDirection (void){return ballDirection;} 
	BallPower getBallPower (void) { return ballPower; }
	GuardLeak getGuardLeak (void){ return guardLeak;} 
	VecPosition getPredictedBallPos(){return predictedBallPos;}
protected: 
	void analyseBallSpeed (double curX, 
		double curY, 
		double lastX, 
		double lastY);				// 分析的速度 
	void analyseBallDirection (double curX, 
		double curY, 
		double lastX, 
		double lastY);			// 分析球的运动方向 
	void analyseBallPower ( Enviornment_Info * env);		// 分析球的控件权 
	void analyseGuardLeak ( Enviornment_Info *env);		// 分析防守漏洞情况	 

protected: 
	AreaInfo		*ballArea;			// 球所在的区域 
	BallSpeed		ballSpeed;			// 球的速度 
	BallDirection	ballDirection;		// 球的运动方向 
	BallPower		ballPower;			// 球的控制权 
	GuardLeak		guardLeak;			// 防守漏洞情况
	VecPosition predictedBallPos;
	//
	AreaManager 	areaMgr;			// 管理区域信息 
}; // end class BallFieldState 

class Analyse_Info{
public:
	BallFieldState &getBallFieldState(){return ballFiedlState;}
private:
	BallFieldState ballFiedlState;
};

class Enviornment_Info{
public:
	enum { ROBOT_NUMBER = PLAYERS_PER_SIDE };
	RobotPID & getRobot(int index) { return robots[index]; }
	RobotBasis & getOpponent(int index) { return oppRobots[index]; }
	RobotPID *getRobots(){return robots;}
	RobotBasis *getOpponents(){return oppRobots;}
	BallBasis & getBall() { return ball; }
	GameState & getGameState() { return gameState; }
	//setter
	inline void setGameState(GameState gs){gameState=gs;}
	//inline bool setBall(const BallBasis ball) {this->ball.Update(ball.getPosition(),  ball.getTheta());return true;}
	/*inline bool setRobot(const RobotBasis robot, int index) {
		if (index < ROBOT_NUMBER && 0<=index) {
			robots[index].Update(robot.getPosition(),robot.getVector(),robot.getTheta());
		}
		else {
			return false;
		}
		return true;
	}*/
	/*inline bool setOpponent(const RobotBasis opponent, int index){
		if (index < ROBOT_NUMBER && 0<=index) {
			oppRobots[index].Update(opponent.getPosition(),opponent.getVector(),opponent.getTheta());
		}
		else {
			return false;
		}
		return true;
	}*/
	LastRole &getLastRole(){return lastRole;}
	void setAnalyseInfo(Analyse_Info *p){analyseInfo=p;}
	Analyse_Info * getAInfo(){return analyseInfo;}
private:
	GameState gameState;
	BallBasis ball;
	RobotPID robots[ROBOT_NUMBER];
	RobotBasis oppRobots[ROBOT_NUMBER];
	//
	Analyse_Info *analyseInfo;
	LastRole lastRole;
};
class StrategyBasis {
public:
	enum { ROBOT_NUMBER = PLAYERS_PER_SIDE };
	//getter
	const Logger & getLogger()const { return logger; }
	const Enviornment_Info *getEnvInfo()const {return info;}
	const GameState & getGameState()const { return info->getGameState(); }
	RobotBasis & getRobot(int index) { return info->getRobot(index); }
	//setter
	inline void setGameState(GameState gs){info->setGameState(gs);}
	//main entry:
	StrategyBasis(char *scriptFile="DebugData.txt",int loggerType=0,char *logFile="DebugLog_1.txt");//init the logger and scriptsystem.
	void Start( Object objects[]);//the entry point,it revoke PreProcess,DecisionMaking,PostProcess
	virtual ~StrategyBasis() {delete info;delete analyseInfo;}
private:

	void PreProcess();
	void DecisionMaking();//we assume the robot is always in the left side
	void PostProcess();
	//
	Enviornment_Info *info;
	Analyse_Info *analyseInfo;
	TeamManager		teamMgr;			// 队形管理 
	RoleManager		roleMgr;			// 角色管理 
	//
	Logger logger;
	// Disallow copy and assign
	StrategyBasis(const StrategyBasis &) {}
	void operator= (const StrategyBasis &) {}
};
class Strategy:public StrategyBasis{
};
#endif  // NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_