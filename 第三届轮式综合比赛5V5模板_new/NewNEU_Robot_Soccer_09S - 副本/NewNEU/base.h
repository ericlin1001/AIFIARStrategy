/**************************************************************************************************** 
base.h 艾数机器人足球策略 状态信息枚举体,公用方法 
 
Purpose: 
	角色可以使用的动作 
 
author: 
	yy_cn 
 
Created Time: 
	2006-5-8 
****************************************************************************************************/ 
 
#ifndef __ROBOT_BASE_H__ 
#define __ROBOT_BASE_H__ 
 
#include <afxcom_.h> 
#include <math.h> 
#include <algorithm> 
#include <vector> 
#include "OutInterFace.h" 
 
using namespace std; 
 
const double BALL_DIAMETER = 4.3180;							// 球的直径 
const double ROBOT_DIAMETER = 7.9756;							// 机器人的直径 
 
const double FIELD_WIDTH = FRIGHTX - FLEFTX;					// 球场宽 
const double FIELD_HEIGHT = FTOP - FBOT;						// 球场高 
 
const double FIELD_CENTER_Y = (FTOP - FBOT) / 2 + FBOT;			// 球场的中心位置 Y 
 
const double FORBIDDEN_ZONE_X = 19.8003;						// 我方禁区 X 坐标 
 
const double OPP_GOAL_CENTER_X = FRIGHTX + ROBOT_DIAMETER;		// 对方球门中心点，对方球场边线 + 1个机器人位置 
const double OPP_GOAL_CENTER_Y = FIELD_CENTER_Y;				// 对方球门的中心点 Y 位置 
const double OPP_SMALL_FORBID_ZONE_X = 88.2806;					// 对方小禁区的 X 坐标 
 
const double SMALL_FORBID_ZONE_TOPY = 52.9284;					// 小禁区上边界 
const double SMALL_FORBID_ZONE_BOTY = 33.7197;					// 小禁区下边界 
const double SMALL_FORBID_ZONE_X = 11.9571;						// 我方小禁区的 X 坐标 
 
const double FORBID_ZONE_X = 19.8003;							// 我方禁区 X 坐标 
const double OPP_FORBID_ZONE_X = 80.4374;						// 对方禁区 X 坐标 
 
// 
// 我方守门员默认位置 
// 
const double GOAL_CENTER_X = FLEFTX + ROBOT_DIAMETER / 3;		// 球门的中心点 X + 半个机器人位置 
const double GOAL_CENTER_Y = FIELD_CENTER_Y;					// 球门的中心点 Y 位置 
 
const double ATTACK_DEFEND_X = FLEFTX + FIELD_WIDTH / 4;		// 进攻后卫的默认 X 
const double ATTACK_DEFEND_Y = FIELD_CENTER_Y;					// 进攻后卫的默认 Y 
 
// 
// 我方后卫位置 
// 
const double DEFEND_TOP_X = 37.2016;							// X 
 
const double DEFEND_LEFT_TOP_X = 17.6934;						// 左上后卫的默认位置 
const double DEFEND_LEFT_TOP_Y = 58.5660; 
 
const double DEFEND_LEFT_BOT_X = DEFEND_LEFT_TOP_X;				// 左下后卫的默认位置 
const double DEFEND_LEFT_BOT_Y = 27.8966; 
 
const double DEFEND_RIGHT_TOP_X = 27.8173;						// 右上后卫默认位置 
const double DEFEND_RIGHT_TOP_Y = 66.2858; 
 
const double DEFEND_RIGHT_BOT_X = 27.8173;						// 右下后卫默认位置 
const double DEFEND_RIGHT_BOT_Y = 19.9442; 
 
// 
// 我方所在的球场方向 
// 
enum BallField 
{ 
	BF_UNKNOWN,				// 未知状态 
	BF_IS_LEFT,				// 左半场 
	BF_IS_RIGHT,			// 右半场 
}; // end enum BallField 
 
// 
// 球在球场上的区域 
// 
enum BallArea 
{ 
	BA_UNKNOWN,				// 未知区域 
	BA_1, BA_2, BA_3, BA_4, BA_5, 
	BA_6, BA_7, BA_8, BA_9, BA_10, 
	BA_11, BA_12, BA_13, BA_14, BA_15, 
	BA_16, BA_17, BA_18, BA_19, BA_20, 
}; // end enum BallArea 
 
// 
// 球的速度信息 
// 
enum BallSpeed 
{ 
	BS_UNKNOWN,				// 未知速度 
	BS_LOW,					// 低速 
	BS_MIDDLE_LOW,			// 中低速 
	BS_MIDDLE,				// 中速 
	BS_HIGH,				// 高速 
	BS_MORE_HIGH,			// 最高速 
}; // end enum BallSpeed 
 
// 
// 球的运动方向 
// 
enum BallDirection 
{ 
	BD_UNKNOWN,				// 未知方向 
	BD_REST,				// 静止 
	BD_RIGHT,				// 右 
	BD_RIGHT_TOP,			// 右上 
	BD_TOP,					// 上 
	BD_LEFT_TOP,			// 左上 
	BD_LEFT,				// 左 
	BD_LEFT_BOTTOM,			// 左下 
	BD_BOTTOM,				// 下 
	BD_RIGHT_BOTTOM,		// 右下 
}; // end enum BallDirection 
 
// 
// 球的控制权 
// 
enum BallPower 
{ 
	BP_UNKNOWN,				// 未知状态 
	BP_OPPONENT,			// 敌方控制 
	BP_CONFRONT,			// 双方顶牛，对峙 
	BP_SELF,				// 我方控球 
	BP_WITHOUT,				// 双方皆不控球 
}; // enum BallPower 
 
// 
// 防守漏洞 
// 
enum GuardLeak 
{ 
	GL_UNKNOWN,				// 未知状态 
	GL_OPPONENT_MORE_BIG,	// 敌方漏洞很大 
	GL_OPPONENT_BIG,		// 敌方漏洞大 
	GL_OPPONENT_SMALL,		// 敌方漏洞小 
	GL_SELF_SMALL,			// 我方漏洞小 
	GL_SELF_BIG,			// 我方漏洞大 
	GL_SELF_MORE_BIG,		// 我方漏洞很大 
}; // end enum GuardLeak 
 
// 
// 机器人角色类型 
// 
enum RoleType 
{ 
	RT_GOALKEEPER,		// 守门员角色 
 
	// 
	// 进攻型角色 
	// 
	PT_ATTACK,			// 进攻者 - 负责中路等待配合并进攻 
	PT_VANGUARD_TOP,	// 上前锋 - 进攻时负责上半个球场 
	PT_VANGUARD_BOTTOM,	// 下前锋 - 进攻时负责下半个球场 
	PT_ATTACK_DEFEND,	// 进攻后卫 - 选择进攻队形时负责防守的机器人 
 
	// 
	// 防守型角色 
	// 
	PT_DEFEND_LEFT_TOP,	// 左上角的后卫 
	PT_DEFEND_LEFT_BOT,	// 左下角的后卫 
	PT_DEFEND_RIGHT_TOP,// 右上角的后卫 
	PF_DEFEND_RIGHT_BOT,// 右下角的后卫 
 
/* 
	RT_POINT_BALL,		// 点球角色 
	PT_DOOR_BALL,		// 门球角色 
	PT_CONTEST_BALL,	// 争球角色 
	PT_FREE_KICK,		// 任意球角色 
 
	PT_SHOOT,			// 射门角色 - 中路、边路...射门角色，因时间不够暂时不细分 
	PT_REPAIR,			// 补射角色 - 中路补射... 
*/ 
	RT_UNKNOWN,			// 未知角色 
}; // end enum RoleType 
 
// 
// 队形编号 - 只是用来方便记忆和描述 
// 
enum TeamNumber 
{ 
	TN_ATTACK,		// 进攻队形 
	TN_DEFEND,		// 防守队形 
}; // end enum Team 
 
// 
// 记录上一次分配的角色与对应的机器人 
// 
struct LastRole 
{ 
	LastRole (void) 
	{ 
		for (int i = 0; i<PLAYERS_PER_SIDE; ++i) 
			role[i] = RT_UNKNOWN; 
	} 
 
	// 
	// 索引值对应的为机器人索引号 
	// 如 role[0] == RT_UNKNOWN 则为 机器人 0 上一次分配的角色为未知角色 
	// 
	RoleType role[PLAYERS_PER_SIDE]; 
}; // struct LastRole 
 
// 
// 删除 
// 
template <typename T> 
struct delete_t 
{ 
	void operator () (T *p) 
	{ 
		delete p; 
		p = 0; 
	} 
}; // end struct delete_t 
 
/** 
 * 跟据给定的 x 位置分析场地信息 
 * 在 Strategy 方法的最开始处调用 
 */ 
BallField analyseFieldInfo (double x = -1.0); 
 
/** 
 * 跟据比赛实际情况转换坐标，转换为从左向右进攻 
 */ 
void transform (double &x, double &y); 
 
/** 
 * 跟据比赛实际情况转换坐标，转换为从左向右进攻 
 */ 
void transform (double &rotation); 
 
/** 
 * 点 pointX, pointY 是否在 
 * 点 topX, topY - topX, topY 的区域内 
 * 机器人足球中 topY > botY 
 */ 
bool isComprise (double topX, double topY, double botX, double botY, double pointX, double pointY); 
 
/** 
 * 获得两点之间的距离 
 */ 
double getDistance (double x1, double y1, double x2, double y2); 
 
/** 
 * 获得跟据两点之间的角度形成的直线映射到给定的 X 点处的高度距离 
 * x1, y1 -> # 
 * x2, y2 -> @ 
 * targetX, targetY -> (*) 
 */ 
double getMappedTargetY (double x1, double y1, double x2, double y2, double targetX); 
 
/** 
 * 获得离球最近的球员编号以及距离 
 */ 
template<typename T> 
void getVicinityPoint (const T *robots, double curX, double curY, long &index, double &distance) 
{ 
	/* 
		队员与球的位置有四种情况 
	 
		+-----------------+ 
		+    1      2     + 
		+       []        + 
		+    3      4     + 
		+-----------------+ 
	 
		1. ((curX - 队员.x)^2 + (队员.y - curY)^2)~2 
		2. ((队员.x - curX)^2 + (队员.y - curY)^2)~2 
		3. ((curX - 队员.x)^2 + (curY - 队员.y)^2)~2 
		4. ((队员.x - curX)^2 + (curY - 队员.y)^2)~2 
	 
		((maxX - minX)^2 + (maxY - minY)^2)~2 
	*/ 
	 
	double robotX = 0; 
	double robotY = 0; 
 
	double maxX = 0; 
	double minX = 0; 
 
	double maxY = 0; 
	double minY = 0; 
 
	index = 0;			// 记录离球最近的对员 
	distance = 0;		// 最短距离 
 
	for (long i = 0; i  PLAYERS_PER_SIDE; ++i) { 
		robotX = robots[i].pos.x; 
		robotY = robots[i].pos.y; 
 
		transform (robotX, robotY); 
 
		if (robotX > curX) { 
			maxX = robotX; 
			minX = curX; 
		} 
		else { 
			maxX = curX; 
			minX = robotX; 
		} 
 
		if (robotY > curY) { 
			maxY = robotY; 
			minY = curY; 
		} 
		else { 
			maxY = curY; 
			minY = robotY; 
		} 
 
		// 
		// 获得距离 
		// 
		double tempDistance = getDistance (maxX, maxY, minX, minY); 
		if (i == 0) { 
			distance = tempDistance; 
		} 
		else { 
			if (distance > tempDistance) { 
				distance = tempDistance; 
				index = i; 
			} 
		} 
	} 
} 
 
#endif // __ROBOT_BASE_H__ 