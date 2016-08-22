/**************************************************************************************************** 
action.h ���������˽�ɫ����ͷ�ļ� 
 
Purpose: 
	��ɫ����ʹ�õĶ��� 
 
author: 
	yy_cn 
	 
Created Time: 
	2006-5-10 
****************************************************************************************************/ 
 
#ifndef __ROBOT_ACTION_H__ 
#define __ROBOT_ACTION_H__ 
 
#include "base.h" 
 
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
void actVelocity (Robot &robot, int vl, int vr); 
 
//	/** 
//	 * ��������ĳ�������˶� 
//	 */ 
//	static void move (Robot &robot, BallDirection direction); 
 
/** 
 * ԭ��������ָ���Ƕ� 
 * @param -180  angle  180 
 */ 
void actTurn (Robot &robot, double angle); 
 
/** 
 * ���������ƶ���ָ��λ�� 
 */ 
void actToPosition (Robot &robot, double x, double y); 
 
// 
// �ɻ���������ɵĸ��Ӷ��� 
// 
 
/** 
 * ���� 
 * ����ǶȻ�λ����ȷ���ʹ���ƶ������ƶ������ʵ�λ�� 
 */ 
void actShoot (Robot &robot, const Environment &env); 
 
/** 
 * ���� 
 * ������������������ʹ���� 
 * @return == true �����ߣ�������˻����˵������� 
 *         == false �������ߣ�δ�����κβ�������һ������������������ 
 */ 
bool actKickBall (Robot &robot, const Environment &env); 
 
/** 
 * ���� 
 */ 
void actReaveBall (Robot &robot); 
 
/** 
 * ���� 
 */ 
void actPassBall (Robot &robot); 
 
/** 
 * ��ָ���ĵз� 
 */ 
void actBlockMan (Robot &robot, const OpponentRobot &opponent); 
 
///** 
// * ��λ 
// */ 
//void pointWaiting (Robot &robot); 
// 
///** 
// * �߽紦�� 
// */ 
//void boundProcess (Robot &robot); 
 
#endif // __ROBOT_ACTION_H__ 