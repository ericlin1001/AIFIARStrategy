#include "stdafx.h"
#include "BallFieldAnalyse.h"
BallFieldState::BallFieldState (void)   
	: _ballArea (0)                 // 球所在的区域   
	, _ballSpeed (BS_UNKNOWN)       // 球的速度   
	, _ballDirection (BD_UNKNOWN)   // 球的运动方向   
	, _ballPower (BP_UNKNOWN)       // 球的控制�?   
	, _guardLeak (GL_UNKNOWN)       // 防守漏洞情况   
	, _areaMgr ()                   // 管理区域信息   
{   
}   

// public   
BallFieldState::~BallFieldState (void)   
{      
}   

// public   
void   
	BallFieldState::analyse (const MyEnvironment &env)
{   
	//   
	// 分析球所在的区域   
	//   
	analyseBallArea (env.currentBall.pos.x, env.currentBall.pos.y);   

	//   
	// 分析球的速度   
	//     
	analyseBallSpeed (env.currentBall.pos.x, env.currentBall.pos.y, env.lastBall.pos.x, env.lastBall.pos.y);   

	//   
	// 分析球的运动方向   
	//   
	analyseBallDirection (env.currentBall.pos.x, env.currentBall.pos.y, env.lastBall.pos.x, env.lastBall.pos.y);   

	//   
	// 分析球的控件�?   
	//   
	analyseBallPower (env);   

	//   
	// 分析防守漏洞情况   
	//   
	analyseGuardLeak (env);   
}   

// protected   
void   
	BallFieldState::predictBall (MyEnvironment &env)   
{   
	//   
	// 预测球的下次移动位置   
	//   
	if(env.lastBall.pos.x==-1)env.predictedBall=env.currentBall;
	else{
	double dx = env.currentBall.pos.x - env.lastBall.pos.x;   
	double dy = env.currentBall.pos.y - env.lastBall.pos.y;   

	env.predictedBall.pos.x = env.currentBall.pos.x + dx;   
	env.predictedBall.pos.y = env.currentBall.pos.y + dy;  
	}
}   

// protected   
void   
	BallFieldState::analyseBallArea (double x, double y)   
{   
	//   
	// 分析球所在的区域   
	//   

	_ballArea = const_cast<AreaInfo*> (_areaMgr.getArea (x, y));   
}   

// protected   
void   
	BallFieldState::analyseBallSpeed (double curX, double curY, double lastX, double lastY)   
{   
	//   
	// 分析球的速度   
	//   
	double distance = getDistance (curX, curY, lastX, lastY);   

	_ballSpeed = BS_LOW;   

	if (distance <= BALL_DIAMETER / 8) {   
		//   
		_ballSpeed = BS_LOW;   
	}   
	else if (distance > BALL_DIAMETER / 8 && distance <= BALL_DIAMETER / 4) {   
		_ballSpeed = BS_MIDDLE_LOW;   
	}   
	else if (distance > BALL_DIAMETER / 4 && distance <= BALL_DIAMETER / 2) {   
		_ballSpeed = BS_MIDDLE;   
	}   
	else if (distance > BALL_DIAMETER / 2 && distance <= BALL_DIAMETER) {   
		_ballSpeed = BS_HIGH;   
	}   
	else if (distance > BALL_DIAMETER) {   
		_ballSpeed = BS_MORE_HIGH;   
	}   
}   

// protected   
void   
	BallFieldState::analyseBallDirection (double curX, double curY, double lastX, double lastY)   
{   


	if (curX == lastX && curY  == lastY) {   
		_ballDirection = BD_REST;           // 静止   
	}   
	else if (curX == lastX && curY > lastY) {   
		_ballDirection = BD_TOP;            // �?   
	}   
	else if (curX == lastX && curY < lastY) {   
		_ballDirection = BD_BOTTOM;         // �?   
	}   
	else if (curX > lastX && curY == lastY) {   
		_ballDirection = BD_RIGHT;          // �?   
	}   
	else if (curX  <lastX && curY == lastY) {   
		_ballDirection = BD_LEFT;           // �?   
	}   
	else if (curX > lastX && curY > lastY) {   
		_ballDirection = BD_RIGHT_TOP;      // 右上   
	}   
	else if (curX > lastX && curY < lastY) {   
		_ballDirection = BD_RIGHT_BOTTOM;   // 右下   
	}   
	else if (curX < lastX && curY > lastY) {   
		_ballDirection = BD_LEFT_TOP;       // 左上   
	}   
	else if (curX < lastX && curY < lastY) {   
		_ballDirection = BD_LEFT_BOTTOM;    // 左下     
	}   
}   

// protected   
void   
	BallFieldState::analyseBallPower (const MyEnvironment &env)   
{   
	//   
	// 分析球的控件�?   
	//   
	double curBallX = env.currentBall.pos.x;   
	double curBallY = env.currentBall.pos.y;   

	//   
	// 判断当前离球最近的队员是我方还是敌�?   
	//   
	long myRobot = 0;                               // 记录我方离球最近的对员   
	double myDistance = 0;                          // 最短距�?   
	getVicinityPoint <Robot> ((Robot *) &env.home, curBallX, curBallY, myRobot, myDistance);   

	long opponentRobot = 0;                         // 记录敌方离球最近的对员   
	double opponentDistance = 0;                    // 最短距�?   
	getVicinityPoint <OpponentRobot> ((OpponentRobot*)&env.opponent,   
		curBallX,   
		curBallY,   
		opponentRobot,   
		opponentDistance);   

	double controlDistance = BALL_INFO::RADIUS+ROBOT_INFO::HALF_LENGTH*1.4143;   
	if (myDistance < controlDistance && opponentDistance > controlDistance) {   
		_ballPower = BP_SELF;                       // 我方控球   
	}   
	else if (myDistance > controlDistance && opponentDistance < controlDistance) {   
		_ballPower = BP_OPPONENT;                   // 敌方控球   
	}   
	else if (myDistance <= controlDistance && opponentDistance <= controlDistance) {   
		_ballPower = BP_CONFRONT;                   // 双方顶牛，对�?   
	}   
	else {   
		_ballPower = BP_WITHOUT;                    // 双方皆不控球   
	}      
}   

// protected   
void   
	BallFieldState::analyseGuardLeak (const MyEnvironment &env)   
{   
	//   
	_guardLeak = GL_OPPONENT_MORE_BIG;   
}   
//**************************************************************************************
