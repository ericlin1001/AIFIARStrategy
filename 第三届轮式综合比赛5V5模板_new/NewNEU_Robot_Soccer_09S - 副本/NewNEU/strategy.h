#ifndef NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_
#define NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_

#include "defines.h"
#include "interface.h"
#include "objects.h"

#include "field_information.h"
#include "scripting_system.h"
#include "logger.h"
// By Code_B_Silence, NEU China
class StrategyBasis {
public:
	const RobotBasis & get_robot(int index)const { return robots_[index]; }//main interface.
	const Object & get_opponent(int index)const { return opponents_[index]; }
	const BallBasis & get_ball()const { return ball_; }
	const DEGame & get_deg()const { return deg_; }

	const FieldInformationBasis & get_field_information()const {return field_information_; }
	const ScriptingSystem & get_filedata()const { return filedata_; }
	const Logger & get_logger()const { return logger_; }
	const DataDebug & get_debugdata()const { return debugdata_; }
	//
	void set_deg(DEGame deg) { deg_ = deg; }//
	void set_debugdata(DataDebug debugdata) { debugdata_ = debugdata; }
	//
	inline bool set_ball(const BallBasis ball);
	inline bool set_robot(const RobotBasis robot, int index);
	inline bool set_opponent(const RobotBasis opponent, int index);

	StrategyBasis(char *scriptFile="DebugData.txt",int loggerType=0,char *logFile="DebugLog_1.txt");//init the logger and scriptsystem.
	void Start(const Object objects[]);//the entry point,it revoke PreProcess,DecisionMaking,PostProcess
	virtual ~StrategyBasis() {}
private:
	//BasicScriptServer scriptServer;
	//
	enum { ROBOT_NUMBER = 5 };
	void PreProcess();
	void DecisionMaking();//we assume the robot is always in the left side
	void PostProcess();
	//
	DEGame deg_;
	BallBasis ball_;
	RobotPID robots_[ROBOT_NUMBER];
	RobotBasis opponents_[ROBOT_NUMBER];
	//
	FieldInformationBasis field_information_;
	ScriptingSystem filedata_;
	Logger logger_;
	DataDebug debugdata_;
	RobotSimple robotPID_;  // For test;
	;
	
	// Disallow copy and assign
	StrategyBasis(const StrategyBasis &) {}
	void operator= (const StrategyBasis &) {}
};
#endif  // NEWNEU_ROBOT_SOCCER_09S_STRATEGY_H_