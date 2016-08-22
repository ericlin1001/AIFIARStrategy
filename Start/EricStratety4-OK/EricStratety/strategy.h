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

#endif  // NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_