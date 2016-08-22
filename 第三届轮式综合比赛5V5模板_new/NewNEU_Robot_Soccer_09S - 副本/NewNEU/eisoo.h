/**************************************************************************************************** 
eisoo.h 艾数机器人足球策略头文件 
 
Purpose: 
	策略头文件,包括区域管理，状态分析 
 
author: 
	yy_cn 
 
Created Time: 
	2006-5-8 
****************************************************************************************************/ 
 
#ifndef __ROBOT_EISOO_H__ 
#define __ROBOT_EISOO_H__ 
 
#include "base.h" 
#include "area.h" 
#include "robotrole.h" 
#include "teamorder.h" 
 
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
	void analyse (const Environment &env); 
 
	/** 
	 * 预估小球的位置 
	 */ 
	void predictBall (Environment &env); 
 
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
	void analyseBallPower (const Environment &env);		// 分析球的控件权 
	void analyseGuardLeak (const Environment &env);		// 分析防守漏洞情况	 
	 
protected: 
	AreaInfo		*_ballArea;			// 球所在的区域 
	BallSpeed		_ballSpeed;			// 球的速度 
	BallDirection	_ballDirection;		// 球的运动方向 
	BallPower		_ballPower;			// 球的控制权 
	GuardLeak		_guardLeak;			// 防守漏洞情况 
 
	AreaManager 	_areaMgr;			// 管理区域信息 
}; // end class BallFieldState 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 决策系统 
// 
class DecisionSystem 
{ 
public: 
	DecisionSystem (void); 
	~DecisionSystem (void); 
 
public: 
	/** 
	 * 策略 
	 */ 
	void strategy (Environment *env); 
 
protected: 
	BallFieldState	_ballFieldState;	// 球场状态信息 
	TeamManager		_teamMgr;			// 队形管理 
	RoleManager		_roleMgr;			// 角色管理 
 
	LastRole		_lastRole;			// 上一次角色分配 
}; // end class DecisionSystem 
 
#endif // __ROBOT_EISOO_H__ 


