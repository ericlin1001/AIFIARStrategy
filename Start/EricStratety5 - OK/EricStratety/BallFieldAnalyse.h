#ifndef BALLFIELDANALYSE_H
#define BALLFIELDANALYSE_H
#include "base.h"
#include "area.h"
#include "strategy.h"

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
	void analyse (const MyEnvironment &env); 
	/** 
	* Ԥ��С���λ�� 
	*/ 
	void predictBall (MyEnvironment &env); 
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
	void analyseBallPower (const MyEnvironment &env);		// ������Ŀؼ�Ȩ 
	void analyseGuardLeak (const MyEnvironment &env);		// ��������©�����	 

protected: 
	AreaInfo		*_ballArea;			// �����ڵ����� 
	BallSpeed		_ballSpeed;			// ����ٶ� 
	BallDirection	_ballDirection;		// ����˶����� 
	BallPower		_ballPower;			// ��Ŀ���Ȩ 
	GuardLeak		_guardLeak;			// ����©����� 

	AreaManager 	_areaMgr;			// ����������Ϣ 
}; // end class BallFieldState 
//************************************************************************
// public  

#endif