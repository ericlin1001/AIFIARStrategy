/**************************************************************************************************** 
action.h ���������˽�ɫ����ͷ�ļ� 
 
Purpose: 
	��ɫ����ʹ�õĶ��� 
 

****************************************************************************************************/ 
 
#ifndef __ROBOT_ACTION_H__ 
#define __ROBOT_ACTION_H__ 
 
#include "base.h" 
#include "objects.h"
#include "strategy.h"
/** 
 * robot �Ƿ�������� 
 * robotX �����˵� X ���� 
 * robotY �����˵� Y ���� 
 * ballX ��� X ���� 
 * ballY ��� Y ���� 
 * ����Ҫ������ת�� 
 * @return == true �������� 
 * @return == false ���������� 
 */ 
bool canShoot (double robotX, double robotY, double ballX, double ballY); 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ����ϵͳ���ṩ�����˽�ɫ��һϵͳ����֧�� 
// 
// 
// �����������ɻ�����������ϳɸ��ӵĶ��� 
// 
 
/** 
 * ����С������ 
 */ 
void actVelocity (RobotPID &robot, int vl, int vr); 
 
//	/** 
//	 * ��������ĳ�������˶� 
//	 */ 
//	static void move (RobotPID &robot, BallDirection direction); 
 
/** 
 * ԭ��������ָ���Ƕ� 
 * @param -180  angle  180 
 */ 
void actTurn (RobotPID &robot, double angle); 
 
/** 
 * ���������ƶ���ָ��λ�� 
 */ 
void actToPosition (RobotPID &robot, double x, double y); 
 
// 
// �ɻ���������ɵĸ��Ӷ��� 
// 
 
/** 
 * ���� 
 * ����ǶȻ�λ����ȷ���ʹ���ƶ������ƶ������ʵ�λ�� 
 */ 
void actShoot (RobotPID &robot,Enviornment_Info &env); 
 
/** 
 * ���� 
 * ������������������ʹ���� 
 * @return == true �����ߣ�������˻����˵������� 
 *         == false �������ߣ�δ�����κβ�������һ������������������ 
 */ 
bool actKickBall (RobotPID &robot,Enviornment_Info &env); 
 
/** 
 * ���� 
 */ 
void actReaveBall (RobotPID &robot); 
 
/** 
 * ���� 
 */ 
void actPassBall (RobotPID &robot); 
 
/** 
 * ��ָ���ĵз� 
 */ 
void actBlockMan (RobotPID &robot, const RobotBasis &opp); 
 
///** 
// * ��λ 
// */ 
//void pointWaiting (RobotPID &robot); 
// 
///** 
// * �߽紦�� 
// */ 
//void boundProcess (RobotPID &robot); 
 
#endif // __ROBOT_ACTION_H__ 