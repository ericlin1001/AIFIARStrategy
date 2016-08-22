#include "stdafx.h"
#include "strategy.h"

#include <iostream>

// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
// Constructor.
StrategyBasis::StrategyBasis(char *scriptFile,int loggerType,char *logFile) {
	filedata_.SetFile(scriptFile);
	if (!loggerType) logger_.OpenConsole();else logger_.OpenFile(logFile);

}

// Entrance of the strategy.
void StrategyBasis::Start(const Object objects[]) {
	// Copy parameters information to local members
	for (int i = 0; i < ROBOT_NUMBER; ++i) {
		robots_[i].Update(objects[i].get_position(), 
			objects[i].get_vector(),
			objects[i].get_theta());
		opponents_[i].Update(objects[ROBOT_NUMBER + i].get_position(),
			objects[ROBOT_NUMBER + i].get_vector(),
			objects[ROBOT_NUMBER + i].get_theta());
	}
	ball_.Update(objects[ROBOT_NUMBER * 2].get_position(),
		objects[ROBOT_NUMBER * 2].get_vector(),
		objects[ROBOT_NUMBER * 2].get_theta());
	// Process strategy
	PreProcess();
	DecisionMaking();
	PostProcess();
}

// Pre-process.
void 
	StrategyBasis::PreProcess() {
		// For better convenience, shift coordinate to 
		// keep home field always on the left side.
		if (FieldInfo::Area::RIGHT == deg_.nDEGameGround) {
			for (int i = 0; i < ROBOT_NUMBER; ++i) {
				//make a central symmetry
				robots_[i].set_position(this->field_information_.get_field_vec()-robots_[i].get_position());
				robots_[i].set_theta(VecPosition::NormalizeAngle(robots_[i].get_theta() + PI));
				opponents_[i].set_position(this->field_information_.get_field_vec() -opponents_[i].get_position());
				opponents_[i].set_theta(VecPosition::NormalizeAngle(opponents_[i].get_theta() + PI));
			}
			ball_.set_position(this->field_information_.get_field_vec()-ball_.get_position());
		}

		// Respond to match state
		if (deg_.nDEStartMode != FieldInfo::Match_State::UNDER_WAY) {
			// TODO: Add some mark to respond to different situation.
			deg_.nDEStartMode = FieldInfo::Match_State::UNDER_WAY;
		}
}

// Strategy process.
#include<vector>
using namespace std;
#include "BasicScriptServer.h"
void StrategyBasis::DecisionMaking() {
	//************init the scriptInterpreter!**************
	#define OUTPUT_FILE "C:\\out.txt"
	#define INPUT_FILE "C:\\in.txt"
	static BasicScriptServer scriptServer(INPUT_FILE,OUTPUT_FILE);
	scriptServer.check();
	scriptServer.startOutPut();
	//**************end init*********************
	static int mode=0;
	static int args[5];
	static int robotID=1;
	static VecPosition target;
	while(!scriptServer.isEmpty()){
		string script=scriptServer.getScript();
		if(script.compare("getlen")==0){
			scriptServer.getOut()<<this->get_field_information().get_field_length()<<endl;
		}else if(sscanf(script.c_str(),"setMode(%d)",args+0)==1){
			mode=args[0];
			scriptServer.getOut()<<"set mode:"<<mode<<endl;
		}else if(sscanf(script.c_str(),"moveRobot(%d,%d,%d)",args+0,args+1,args+2)==3){
			robotID=args[0];
			target.SetX(args[1]);target.SetY(args[2]);
			scriptServer.getOut()<<"Moving robot("<<robotID<<")"<<endl;
		}else {//cant' recognize
			scriptServer.getOut()<<script<<endl;
		}

	}
	if(mode==0){
		const double ROBOT_LEN=RobotBasis::get_robot_size();
		const int maxSpeed=RobotBasis::get_speed_limit();
		VecPosition ballPos=this->get_ball().get_position();
		VecPosition goalPos(220,90);
		VecPosition dir=goalPos-ballPos;
		dir.SetMagnitude(ROBOT_LEN);
		VecPosition vec_dir=dir;
		vec_dir.Rotate(PI/2);
	
		VecPosition forward=dir;
		forward.SetMagnitude(ROBOT_LEN*0.5);
		robots_[1].ToPositionPD(VecPosition(110,90),RobotBasis::get_speed_limit());
	}else if(mode==1){
		robots_[robotID].ToPositionPD(target,RobotBasis::get_speed_limit());
	}else if(mode==2){
	}else {
	}

	
	//robots_[2].ToPositionPD(ballPos+vec_dir+forward,maxSpeed);
	//robots_[3].ToPositionPD(ballPos-vec_dir+forward,maxSpeed);
	// TODO: Add strategy detail here.

	//***************ending******************
	scriptServer.endOutPut();
	//***************ending******************
}

// Post-process.

void StrategyBasis::PostProcess() {
	
}
// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
