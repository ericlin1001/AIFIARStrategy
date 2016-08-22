#include "stdafx.h"
#include "MyStrategy.h"
#include "objects.h"
#include "BasicScriptServer.h"
#define OUTPUT_FILE "C:\\out.txt"
#define INPUT_FILE "C:\\in.txt"
BasicScriptServer scriptServer(INPUT_FILE,OUTPUT_FILE);
void Strategy::PreProcess(){
	StrategyBasis::PreProcess();
	//
	scriptServer.check();
	scriptServer.startOutPut();
}
void Strategy::PostProcess(){
	scriptServer.endOutPut();
	//
	StrategyBasis::PostProcess();
}

void Strategy::DecisionMaking() {
	static int mode=1;
	static int args[10];
	static int ids[10];
	static VecPosition targets[10];
	static double angles[10];
	static int p=0;
#define target targets[p]
#define angle angles[p]
#define id ids[p]
	//
	while(!scriptServer.isEmpty()){
		string script=scriptServer.getScript();
		if(sscanf(script.c_str(),"setMode(%d)",args+0)==1){
			mode=args[0];
			scriptServer.getOut()<<"set mode:"<<mode<<endl;
		}else if(sscanf(script.c_str(),"moveRobot(%d,%d,%d)",args+0,args+1,args+2)==3){
			p=0;
			id=args[0];
			target.SetX(args[1]);target.SetY(args[2]);
			scriptServer.getOut()<<"Moving robot("<<id<<")"<<endl;
		}else if(sscanf(script.c_str(),"moveAngle(%d,%d)",args+0,args+1)==2){
			p=1;
			angle=args[0];
			target.SetX(args[1]);target.SetY(args[2]);
			scriptServer.getOut()<<"Moving robot("<<id<<")"<<endl;
		}else if(strcmp(script.c_str(),"cm")==0){
			mode=(++mode)%2;
		}else {//cant' recognize
			scriptServer.getOut()<<script<<endl;
		}
	}
	if(mode==0){//normal,run the strategy
		/*const double ROBOT_LEN=RobotBasis::get_robot_size();
		const int maxSpeed=RobotBasis::get_speed_limit();
		VecPosition ballPos=this->get_ball().get_position();
		VecPosition goalPos(220,90);
		VecPosition dir=goalPos-ballPos;
		dir.SetMagnitude(ROBOT_LEN);
		VecPosition vec_dir=dir;
		vec_dir.Rotate(PI/2);
	
		VecPosition forward=dir;
		forward.SetMagnitude(ROBOT_LEN*0.5);
		robots_[1].ToPositionPD(VecPosition(110,90),RobotBasis::get_speed_limit());*/
	}else if(mode==1){
		p=0;
		robots_[id].ToPositionPD(target,ROBOT_INFO::WHEEL::MAX_SPEED);
		p=1;
		robots_[id].TurnToAngle(angle);
	}
	//robots_[2].ToPositionPD(ballPos+vec_dir+forward,maxSpeed);
	//robots_[3].ToPositionPD(ballPos-vec_dir+forward,maxSpeed);
	// TODO: Add strategy detail here.

	
}