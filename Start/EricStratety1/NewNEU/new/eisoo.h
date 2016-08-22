/**************************************************************************************************** 
eisoo.h �����������������ͷ�ļ� 
 
Purpose: 
	����ͷ�ļ�,�����������״̬���� 
 
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
// ���ϵ�״̬��Ϣ 
// 
class BallFieldState 
{ 
public: 
	/** 
	 * ���ϵ�״̬��Ϣ���� 
	 */ 
	BallFieldState (void); 
	~BallFieldState (void); 
 
public: 
	/** 
	 * �������ϵ���Ϣ���޸ļ�¼������Ϣ���Ա���Ҫ�߻�� 
	 */ 
	void analyse (const Environment &env); 
 
	/** 
	 * Ԥ��С���λ�� 
	 */ 
	void predictBall (Environment &env); 
 
	/** 
	 * �����ǰ�������� 
	 */ 
	const AreaInfo *getBallArea (void) 
	{ 
		return _ballArea; 
	} 
	 
	/** 
	 * �����ǰ���ٶ� 
	 */ 
	BallSpeed getBallSpped (void) 
	{ 
		return _ballSpeed; 
	} 
	 
	/** 
	 * �������˶����� 
	 */ 
	BallDirection getBallDirection (void) 
	{ 
		return _ballDirection;	 
	} 
	 
	/** 
	 * �����Ŀؼ�Ȩ 
	 */ 
	BallPower getBallPower (void) 
	{ 
		return _ballPower; 
	} 
	 
	/** 
	 * ��÷���©����� 
	 */ 
	GuardLeak getGuardLeak (void) 
	{ 
		return _guardLeak; 
	} 
	 
protected: 
	 
	void analyseBallArea (double x, double y);			// �������ڵ����� 
	void analyseBallSpeed (double curX, 
						   double curY, 
						   double lastX, 
						   double lastY);				// �������ٶ� 
	void analyseBallDirection (double curX, 
							   double curY, 
							   double lastX, 
							   double lastY);			// ��������˶����� 
	void analyseBallPower (const Environment &env);		// ������Ŀؼ�Ȩ 
	void analyseGuardLeak (const Environment &env);		// ��������©�����	 
	 
protected: 
	AreaInfo		*_ballArea;			// �����ڵ����� 
	BallSpeed		_ballSpeed;			// ����ٶ� 
	BallDirection	_ballDirection;		// ����˶����� 
	BallPower		_ballPower;			// ��Ŀ���Ȩ 
	GuardLeak		_guardLeak;			// ����©����� 
 
	AreaManager 	_areaMgr;			// ����������Ϣ 
}; // end class BallFieldState 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ����ϵͳ 
// 
class DecisionSystem 
{ 
public: 
	DecisionSystem (void); 
	~DecisionSystem (void); 
 
public: 
	/** 
	 * ���� 
	 */ 
	void strategy (Environment *env); 
 
protected: 
	BallFieldState	_ballFieldState;	// ��״̬��Ϣ 
	TeamManager		_teamMgr;			// ���ι��� 
	RoleManager		_roleMgr;			// ��ɫ���� 
 
	LastRole		_lastRole;			// ��һ�ν�ɫ���� 
}; // end class DecisionSystem 
 
#endif // __ROBOT_EISOO_H__ 


