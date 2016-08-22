#include "stdafx.h"
#include "strategy.h"

#include <iostream>
#include "GeometryR.h"
// ---- ---- ---- ---- Class BallFieldState ---- ---- ---- ----
// Constructor.
// public   
BallFieldState::BallFieldState (void)   
	: ballArea (0)                 // 球所在的区域   
	, ballSpeed (BS_UNKNOWN)       // 球的速度   
	, ballDirection (BD_UNKNOWN)   // 球的运动方向   
	, ballPower (BP_UNKNOWN)       // 球的控制�?   
	, guardLeak (GL_UNKNOWN)       // 防守漏洞情况   
	, areaMgr ()                   // 管理区域信息   
{   
}   

// public   
BallFieldState::~BallFieldState (void)   
{      
}   

// public   
void BallFieldState::analyse (Enviornment_Info *env)   
{   
	VecPosition ballPos=env->getBall().getPosition();
	VecPosition oldBallPos=env->getBall().getOldPosition(0);
	//
	ballArea = const_cast<AreaInfo*> (areaMgr.getArea (ballPos.GetX(),ballPos.GetY()));    
	analyseBallSpeed (ballPos.GetX(), ballPos.GetY(),oldBallPos.GetX(),oldBallPos.GetY());   
	analyseBallDirection (ballPos.GetX(),ballPos.GetY(),oldBallPos.GetX(),oldBallPos.GetY());   
	analyseBallPower (env);    
	analyseGuardLeak (env);   
}   

// protected   


// protected   
void BallFieldState::analyseBallSpeed (double curX, double curY, double lastX, double lastY)   
{     
	double distance =(VecPosition(curX, curY)-VecPosition( lastX, lastY)).GetMagnitude();   
	ballSpeed = BS_LOW;
	if (distance <= BALL_INFO::DIAMETER/ 8) {   
		ballSpeed = BS_LOW;   
	}else if (distance > BALL_INFO::DIAMETER / 8 && distance <= BALL_INFO::DIAMETER / 4) {   
		ballSpeed = BS_MIDDLE_LOW;   
	}   
	else if (distance > BALL_INFO::DIAMETER / 4 && distance <= BALL_INFO::DIAMETER / 2) {   
		ballSpeed = BS_MIDDLE;   
	}   
	else if (distance > BALL_INFO::DIAMETER / 2 && distance <= BALL_INFO::DIAMETER) {   
		ballSpeed = BS_HIGH;   
	}   
	else if (distance > BALL_INFO::DIAMETER) {   
		ballSpeed = BS_MORE_HIGH;   
	}  
}   
void   BallFieldState::predictBall (Enviornment_Info *env){   
	this->predictedBallPos=env->getBall().getPosition()+env->getBall().getVector();
}   

// protected   
void  BallFieldState::analyseBallDirection (double curX, double curY, double lastX, double lastY){   
	if (curX == lastX && curY  == lastY) {   
		ballDirection = BD_REST;           // 静止   
	}   
	else if (curX == lastX && curY > lastY) {   
		ballDirection = BD_TOP;            // �?   
	}   
	else if (curX == lastX && curY < lastY) {   
		ballDirection = BD_BOTTOM;         // �?   
	}   
	else if (curX > lastX && curY == lastY) {   
		ballDirection = BD_RIGHT;          // �?   
	}   
	else if (curX < lastX && curY == lastY) {   
		ballDirection = BD_LEFT;           // �?   
	}   
	else if (curX > lastX && curY > lastY) {   
		ballDirection = BD_RIGHT_TOP;      // 右上   
	}   
	else if (curX > lastX && curY < lastY) {   
		ballDirection = BD_RIGHT_BOTTOM;   // 右下   
	}   
	else if (curX < lastX && curY > lastY) {   
		ballDirection = BD_LEFT_TOP;       // 左上   
	}   
	else if (curX < lastX && curY < lastY) {   
		ballDirection = BD_LEFT_BOTTOM;    // 左下     
	}   
}   

// protected   
void  BallFieldState::analyseBallPower ( Enviornment_Info *env)   
{   
	int myRobot = 0;                               
	double myDistance = 0;		              
	int oppRobot = 0;                       
	double oppDistance = 0;  
	double myTemp;
	double oppTemp;
	VecPosition ballPos=env->getBall().getPosition();
	for(int i=0;i<PLAYERS_PER_SIDE;i++){
		myTemp=env->getRobot(i).GetDistanceTo(ballPos);
		if(i==0 || myTemp<myDistance){
			myDistance=myTemp;
			myRobot=i;
		}
		oppTemp=env->getOpponent(i).GetDistanceTo(ballPos);
		if(i==0 || oppTemp<oppDistance){
			oppDistance=oppTemp;
			oppRobot=i;
		}
	}
	double controlDistance = BALL_INFO::RADIUS;
	if (myDistance <= controlDistance && oppDistance > controlDistance) {   
		ballPower = BP_SELF;                       // 我方控球   
	}   
	else if (myDistance > controlDistance && oppDistance <= controlDistance) {   
		ballPower = BP_OPPONENT;                   // 敌方控球   
	}   
	else if (myDistance <= controlDistance && oppDistance <= controlDistance) {   
		ballPower = BP_CONFRONT;                   // 双方顶牛，对�?   
	}   
	else {   
		ballPower = BP_WITHOUT;                    // 双方皆不控球   
	}      
}   

// protected   
void BallFieldState::analyseGuardLeak ( Enviornment_Info* env)   
{   
	guardLeak = GL_OPPONENT_MORE_BIG;   
}   

// ---- ---- ---- ----End Of Class StrategyBasis ---- ---- ---- ----


// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
// Constructor.
StrategyBasis::StrategyBasis(char *scriptFile,int loggerType,char *logFile) {
	if (!loggerType) logger.OpenConsole();else logger.OpenFile(logFile);
	info=new Enviornment_Info();
	analyseInfo=new Analyse_Info();
	info->setAnalyseInfo(analyseInfo);
}

// Entrance of the strategy.
void StrategyBasis::Start( Object objects[]) {
	// If the positions of objects have been reset(in most case caused by the 
	// change of the match state), all objects' displacements will be set to be 0.
	if (info->getGameState().matchState!= MatchState::MS_UNDER_WAY) {
		for (int i = 0; i < ROBOT_NUMBER; ++i) {
			info->getRobot(i).reset();
			info->getOpponent(i).reset();
		}
		info->getBall().reset();
	}

	// For better convenience, shift coordinate to 
	// keep home field always on the left side.
	if(info->getGameState().myField==BallField::RIGHT){
		VecPosition fieldVec=VecPosition(FIELD_INFO::LENGTH,FIELD_INFO::WIDTH);
		for (int i = 0; i < ROBOT_NUMBER*2+1; ++i) {
			objects[i].setPosition(fieldVec-objects[i].getPosition());
			objects[i].setTheta(VecPosition::NormalizeAngle(objects[i].getTheta() + PI));
		}
	}
	//Update the Environment_Info *info;
	for (int i = 0; i < ROBOT_NUMBER; ++i) {
		info->getRobot(i).Update(objects[i].getPosition(),objects[i].getTheta());
		info->getOpponent(i).Update(objects[ROBOT_NUMBER + i].getPosition(),objects[ROBOT_NUMBER + i].getTheta());
	}
	info->getBall().Update(objects[ROBOT_NUMBER * 2].getPosition(),objects[ROBOT_NUMBER * 2].getTheta());
	//end Update
	
	// Process strategy
	PreProcess();
	DecisionMaking();
	PostProcess();

	// Respond to match state
	if(info->getGameState().matchState!=MatchState::MS_UNDER_WAY){
		info->getGameState().matchState=MatchState::MS_UNDER_WAY;
	}
}

// Pre-process.
void StrategyBasis::PreProcess() {
	
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
	this->analyseInfo->getBallFieldState().analyse(info);
	this->analyseInfo->getBallFieldState().predictBall(info);

	TeamOrder *team = teamMgr.getTeam (analyseInfo->getBallFieldState().getBallArea (),   
                                            analyseInfo->getBallFieldState().getBallSpped (),   
                                            analyseInfo->getBallFieldState().getBallDirection (),   
                                            analyseInfo->getBallFieldState().getBallPower (),   
                                            analyseInfo->getBallFieldState().getGuardLeak ());  
	if (team == 0) {   
            //ASSERT (false);   
            return;   
    }
	RoleType *teamRoles= team->getRoles ();   
	if (teamRoles == 0) {   
		//ASSERT (false);   
		return;   
	}   
	int i;
    vector <long> remainRobotIndexs;            
    for ( i = 0; i < PLAYERS_PER_SIDE; ++i)   
        remainRobotIndexs.push_back (i);   
      
       RoleType currentRolesAssigment[PLAYERS_PER_SIDE];   
      
       for (i = 0; i < PLAYERS_PER_SIDE; ++i) {   
            RobotRole *role = roleMgr.getRole (teamRoles[i]);
			int robotIndex = role->assignRobots(info->getRobots(), remainRobotIndexs, info->getLastRole());   
            role->strategy (info->getRobots()[robotIndex],   
				info->getAInfo()->getBallFieldState().getBallArea (),   
                            info->getAInfo()->getBallFieldState().getBallSpped (),   
                            info->getAInfo()->getBallFieldState().getBallDirection (),   
                            info->getAInfo()->getBallFieldState().getBallPower (),   
                            info->getAInfo()->getBallFieldState().getGuardLeak (),   
                            info);  
            currentRolesAssigment[robotIndex] = teamRoles[i];
            //   
            typedef vector <long>::iterator iterator;   
            iterator itend = remainRobotIndexs.end ();   
            for (iterator it = remainRobotIndexs.begin (); it != itend; ++it) {   
                if (*it == robotIndex) {   
                    remainRobotIndexs.erase (it);   
                    break;   
                }   
            }   
        }   
        //   
        // 角色策略都已经执行完�?   
        //   
        // 记录这一次分配的机器人角�?   
        //   
        for ( i = 0; i <PLAYERS_PER_SIDE; ++i)   
			info->getLastRole().role[i] = currentRolesAssigment[i];  
	
	//***************ending******************
	scriptServer.endOutPut();
	//***************ending******************
}

// Post-process.

void StrategyBasis::PostProcess() {

}
// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
