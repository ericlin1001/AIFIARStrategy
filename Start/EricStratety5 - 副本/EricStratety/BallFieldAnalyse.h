#ifndef BALLFIELDANALYSE_H
#define BALLFIELDANALYSE_H
#include "base.h"
#include "area.h"
#include "strategy.h"

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
	void analyse (const MyEnvironment &env); 
	/** 
	* 预估小球的位置 
	*/ 
	void predictBall (MyEnvironment &env); 
	/** 
	* 获得球当前所在区域 
	*/ 
	const AreaInfo *getBallArea (void) 
	{ 
		return _ballArea; 
	} 
	/** 
	* 获得球当前的速度 
	*/ 
	BallSpeed getBallSpped (void) 
	{ 
		return _ballSpeed; 
	} 
	/** 
	* 获得球的运动方向 
	*/ 
	BallDirection getBallDirection (void) 
	{ 
		return _ballDirection;	 
	} 

	/** 
	* 获得球的控件权 
	*/ 
	BallPower getBallPower (void) 
	{ 
		return _ballPower; 
	} 

	/** 
	* 获得防守漏洞情况 
	*/ 
	GuardLeak getGuardLeak (void) 
	{ 
		return _guardLeak; 
	} 

protected: 

	void analyseBallArea (double x, double y);			// 分析所在的区域 
	void analyseBallSpeed (double curX, 
		double curY, 
		double lastX, 
		double lastY);				// 分析的速度 
	void analyseBallDirection (double curX, 
		double curY, 
		double lastX, 
		double lastY);			// 分析球的运动方向 
	void analyseBallPower (const MyEnvironment &env);		// 分析球的控件权 
	void analyseGuardLeak (const MyEnvironment &env);		// 分析防守漏洞情况	 

protected: 
	AreaInfo		*_ballArea;			// 球所在的区域 
	BallSpeed		_ballSpeed;			// 球的速度 
	BallDirection	_ballDirection;		// 球的运动方向 
	BallPower		_ballPower;			// 球的控制权 
	GuardLeak		_guardLeak;			// 防守漏洞情况 

	AreaManager 	_areaMgr;			// 管理区域信息 
}; // end class BallFieldState 
//************************************************************************
// public  

#endif