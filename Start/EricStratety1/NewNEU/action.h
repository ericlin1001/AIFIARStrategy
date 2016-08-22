/**************************************************************************************************** 
action.h 艾数机器人角色动作头文件 
 
Purpose: 
	角色可以使用的动作 
 

****************************************************************************************************/ 
 
#ifndef __ROBOT_ACTION_H__ 
#define __ROBOT_ACTION_H__ 
 
#include "base.h" 
#include "objects.h"
#include "strategy.h"
/** 
 * robot 是否可以射门 
 * robotX 机器人的 X 坐标 
 * robotY 机器人的 Y 坐标 
 * ballX 球的 X 坐标 
 * ballY 球的 Y 坐标 
 * 不需要将坐标转换 
 * @return == true 可以射门 
 * @return == false 不可以射门 
 */ 
bool canShoot (double robotX, double robotY, double ballX, double ballY); 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 动作系统，提供机器人角色的一系统动作支持 
// 
// 
// 基本动作，由基本动作来组合成复杂的动作 
// 
 
/** 
 * 设置小车轮数 
 */ 
void actVelocity (RobotPID &robot, int vl, int vr); 
 
//	/** 
//	 * 机器人向某个方向运动 
//	 */ 
//	static void move (RobotPID &robot, BallDirection direction); 
 
/** 
 * 原地旋传到指定角度 
 * @param -180  angle  180 
 */ 
void actTurn (RobotPID &robot, double angle); 
 
/** 
 * 将机器人移动到指定位置 
 */ 
void actToPosition (RobotPID &robot, double x, double y); 
 
// 
// 由基本动作组成的复杂动作 
// 
 
/** 
 * 射门 
 * 如果角度或方位不正确则会使用移动动作移动到合适的位置 
 */ 
void actShoot (RobotPID &robot,Enviornment_Info &env); 
 
/** 
 * 踢球 
 * 将球往非球门区域方向使劲踢 
 * @return == true 可以踢，并赋与此机器人的踢球动作 
 *         == false 不可以踢，未进行任何操作，上一层跟据情况做其它处理 
 */ 
bool actKickBall (RobotPID &robot,Enviornment_Info &env); 
 
/** 
 * 抢球 
 */ 
void actReaveBall (RobotPID &robot); 
 
/** 
 * 传球 
 */ 
void actPassBall (RobotPID &robot); 
 
/** 
 * 盯指定的敌方 
 */ 
void actBlockMan (RobotPID &robot, const RobotBasis &opp); 
 
///** 
// * 跑位 
// */ 
//void pointWaiting (RobotPID &robot); 
// 
///** 
// * 边界处理 
// */ 
//void boundProcess (RobotPID &robot); 
 
#endif // __ROBOT_ACTION_H__ 