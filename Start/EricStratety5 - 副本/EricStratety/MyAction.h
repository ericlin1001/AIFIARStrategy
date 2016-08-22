#ifndef MYACTION_H
#define MYACTION_H 
#include "base.h" 
#include "strategy.h"
#define Environment MyEnvironment
/** 
������������Basic Actions, BA
		ToPostion 	�����㣨ͣ��
		TurnAngle	ת��һ���Ƕ�
		MoveAlong	��ĳ��(����)�������˶�
		//
		MoveToPt
������������Skilled Actions, SA
		KickBall		    ������
		ShootGoal	    ����
		TurnShoot	    ת������
		DefenseBall	    ���򣨻ط���
		BlockMan	    ���˷���
		AvoidBound	    ��ֹ��ײ�߽�
		//
		KeepGoal 			����Ա����
		ProcessBoundBall 	�߽�����
		ProcessCornerBall 	������
		PassBallToPt 			���򵽶���
		AvoidObstToPt 		���ϰ�������

��϶���(����)
              ����Combinatorial Action, CA
    
ս������(����)
             ����Tactical Actions, TA   
			NormalKickoff 			�г�����
			PassToShoot 			һ��һ��
			BL_PassToCenterShoot 	���ߴ�������

*/ 
void ShootGoal (Robot &robot, const Environment &env);
void EndProcess(Robot &robot, const Environment &env,const VecPosition &goal);
#endif