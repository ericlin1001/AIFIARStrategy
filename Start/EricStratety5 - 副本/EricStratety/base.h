/**************************************************************************************************** 
base.h 

Purpose: 
艾数机器人足球策略 状态信息枚举体,公用方法 
****************************************************************************************************/ 
#ifndef __BASE_H__ 
#define __BASE_H__ 
#include <iostream>
using namespace std;
#define Trace(m) cout<<#m<<"="<<(m)<<endl;
#define Show(m) cout<<m<<endl;

//#include <afxcom_.h> 
#include <math.h> 
#include <algorithm> 
#include <vector> 
using namespace std; 
#define sqrt_2 1.41422
/***********************************
基本单位设定:
质量:g
路程:cm

Y+---------------------------+
^							|
|							|
|							|
|							|
|							|
|							|
|							|
+-------------------------->+
(0,0)                        X
由于在决策时,会将我方转化为在左方向右方进攻,
所以下面的信息均以我方为左方为例!
************************************/
#ifndef PI
#define PI 3.1415926
#endif
#define ASSERT(m) Show("ASSERT("#m");")
const long PLAYERS_PER_SIDE = 5;	

namespace BALL_INFO{
	const double WEIGHT=46;//g
	const double DIAMETER=4.27;//cm
	const double RADIUS=DIAMETER/2;
};
//#define BALL_DIAMETER BALL_INFO::DIAMETER
namespace ROBOT_INFO{
	const double LENGTH=7.5;//xlen
	const double HALF_LENGTH=LENGTH/2;
	const double HALF_DIAGNOL=HALF_LENGTH*sqrt_2;
	//const double WIDTH=7.5;//ylen
	//const double HEIGHT=4.5;
	namespace WHEEL{
		const double MAX_SPEED=100;
		const double MIN_SPEED=-100;
		const double RADIUS=2;
	};
};

namespace FIELD_INFO{
	const double LENGTH=220;
	const double WIDTH=180;
	inline double getCenterX(){return LENGTH/2;}
	inline double getCenterY(){return WIDTH/2;}
	//
	inline double getTop(){return WIDTH;}
	inline double getBot(){return 0;}
	inline double getLEFT(){return 0;}
	inline double getRight(){return LENGTH;}
	namespace FORBIDDEN_AREA{
		const double LENGTH=35;
		const double WIDTH=80;
		inline double getX(){return LENGTH;}
		inline double getOppX(){return FIELD_INFO::LENGTH-LENGTH;}
	};
	namespace GOAL{
		const double WIDTH=40;
		const double DEPTH=15;
		inline double getOppCenterX(){return FIELD_INFO::LENGTH+ROBOT_INFO::LENGTH;}
		inline double getOppCenterY(){return FIELD_INFO::getCenterY();}
		inline double getTop(){return FIELD_INFO::getCenterY()+WIDTH/2;}
		inline double getBot(){return FIELD_INFO::getCenterY()-WIDTH/2;}

	};
	namespace GOAL_AREA{
		const double LENGTH=15;
		const double WIDTH=50;
		inline double getOppX(){return FIELD_INFO::LENGTH-LENGTH;}
		inline double getX(){return LENGTH;}
		inline double getTop(){return FIELD_INFO::getCenterY()+WIDTH/2;}
		inline double getBot(){return FIELD_INFO::getCenterY()-WIDTH/2;}
	};
	namespace WALL{
		const double HEIGHT=5;
		const double THICKNESS=2.5;
	};
	namespace TRIANGLE{
		const double LENGTH=7;
	};
	namespace MIDDLE_CIRCLE{
		const double RADIUS=25;
	};
};

// 我方所在的球场方向 
enum BallField{
	LEFT= 0, 
	RIGHT=1 
};
// 比赛状态 
enum MatchState{ 
	MS_NORMAL = 0, //正常比赛
	MS_FREE_BALL = 1, // 当是自由球 
	MS_PENALTY_KICK = 2,// 点球
	MS_FREE_KICK = 3, // 任意球 
	MS_GOAL_KICK = 4, // 门球 
	MS_UNDER_WAY = 5,//进行中
};
// 发球方
enum BallOwner{
	BO_ANYONE=0,
	BO_SELF=1,
	BO_OPP=2,
};
struct GameState{
	BallField myField;
	MatchState matchState;
	BallOwner ballOwner;
};

//enum PenaltyState{ DEFENSE = 0, ATTACK = 1 };


// 
// 我方守门员默认位置 
// 
const double GOAL_CENTER_X = 0 + ROBOT_INFO::LENGTH / 2;		// 球门的中心点 X + 半个机器人位置 
const double GOAL_CENTER_Y = FIELD_INFO::getCenterY();			// 球门的中心点 Y 位置 

const double ATTACK_DEFEND_X = 0 + FIELD_INFO::LENGTH / 4;		// 进攻后卫的默认 X 
const double ATTACK_DEFEND_Y = FIELD_INFO::getCenterY();		// 进攻后卫的默认 Y 

// 
// 我方后卫位置 
// 
const double DEFEND_TOP_X = FIELD_INFO::LENGTH/4*3/4;							// X 

const double DEFEND_LEFT_TOP_X = FIELD_INFO::LENGTH/4*7/10;						// 左上后卫的默认位置 
const double DEFEND_LEFT_TOP_Y = 120; 

const double DEFEND_LEFT_BOT_X = DEFEND_LEFT_TOP_X;				// 左下后卫的默认位置 
const double DEFEND_LEFT_BOT_Y = FIELD_INFO::WIDTH-DEFEND_LEFT_TOP_Y; 

const double DEFEND_RIGHT_TOP_X = FIELD_INFO::LENGTH/4*13/10;						// 右上后卫默认位置 
const double DEFEND_RIGHT_TOP_Y = 110; 

const double DEFEND_RIGHT_BOT_X = DEFEND_RIGHT_TOP_X;						// 右下后卫默认位置 
const double DEFEND_RIGHT_BOT_Y = FIELD_INFO::WIDTH-DEFEND_RIGHT_TOP_Y; 

// 
const double EDGE		 = BALL_INFO::RADIUS;
const double FLEFTX      = EDGE;							// 场地左边界 
const double FTOP        = FIELD_INFO::WIDTH-EDGE;							// 场地上边界 
const double FRIGHTX     = FIELD_INFO::LENGTH-EDGE;							// 场地右边界 
const double FBOT        = EDGE;							// 场地下边界 

const double GRIGHT      = FIELD_INFO::GOAL::getOppCenterX();							// 球门右边界 
const double GLEFT       = 2.8748;							// 球门左边界 
const double GTOPY       = FIELD_INFO::GOAL::getOppCenterY()+FIELD_INFO::GOAL::WIDTH/2;							// 球门上边界 
const double GBOTY       = FIELD_INFO::GOAL::getOppCenterY()-FIELD_INFO::GOAL::WIDTH/2;							// 球门下边界 
//******************************
const double BALL_DIAMETER = BALL_INFO::DIAMETER;							// 球的直径 
const double ROBOT_DIAMETER = ROBOT_INFO::LENGTH;							// 机器人的直径 
 
const double FIELD_WIDTH = FIELD_INFO::LENGTH;					// 球场宽 
const double FIELD_HEIGHT = FIELD_INFO::WIDTH;						// 球场高 
 
const double FIELD_CENTER_Y = FIELD_INFO::getCenterY();			// 球场的中心位置 Y 
const double FIELD_CENTER_X = FIELD_INFO::getCenterX();			// 球场的中心位置 Y 
  

const double FORBIDDEN_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getX();//19.8003;						// 我方禁区 X 坐标 
 
const double OPP_GOAL_CENTER_X = FRIGHTX + ROBOT_DIAMETER;		// 对方球门中心点，对方球场边线 + 1个机器人位置 
const double OPP_GOAL_CENTER_Y = FIELD_CENTER_Y;				// 对方球门的中心点 Y 位置 
const double OPP_SMALL_FORBID_ZONE_X = FIELD_INFO::GOAL_AREA::getOppX();					// 对方小禁区的 X 坐标 
 
const double SMALL_FORBID_ZONE_TOPY = FIELD_INFO::GOAL_AREA::getTop();					// 小禁区上边界 
const double SMALL_FORBID_ZONE_BOTY = FIELD_INFO::GOAL_AREA::getBot();					// 小禁区下边界 
const double SMALL_FORBID_ZONE_X = FIELD_INFO::GOAL_AREA::getX();						// 我方小禁区的 X 坐标 
 
const double FORBID_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getX();							// 我方禁区 X 坐标 
const double OPP_FORBID_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getOppX();						// 对方禁区 X 坐标 
 
//********************************
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

#define convertBallArea(m) "BA_"<<(m)
#define XX(n) (FIELD_INFO::LENGTH+2*FIELD_INFO::GOAL::DEPTH+2*EDGE)/5*(n)-FIELD_INFO::GOAL::DEPTH-EDGE
#define YY(n) (FIELD_INFO::WIDTH+2*EDGE)/4*(n)-EDGE
#define ADDAREA(x1,y1,x2,y2,area)  addArea(XX(x1),YY(y1),XX(x2),YY(y2),area)
#define Macro_Add_Area	ADDAREA(0,3,1,4,BA_1);				\
						ADDAREA(1,3,2,4,BA_2);				\
						ADDAREA(2,3,3,4,BA_3);				\
						ADDAREA(3,3,4,4,BA_4);				\
						ADDAREA(4,3,5,4,BA_5);				\
						ADDAREA(0,2,1,3,BA_6);				\
						ADDAREA(1,2,2,3,BA_7);				\
						ADDAREA(2,2,3,3,BA_8);				\
						ADDAREA(3,2,4,3,BA_9);				\
						ADDAREA(4,2,5,3,BA_10);				\
						ADDAREA(0,1,1,2,BA_11);				\
						ADDAREA(1,1,2,2,BA_12);				\
						ADDAREA(2,1,3,2,BA_13);				\
						ADDAREA(3,1,4,2,BA_14);				\
						ADDAREA(4,1,5,2,BA_15);				\
						ADDAREA(0,0,1,1,BA_16);				\
						ADDAREA(1,0,2,1,BA_17);				\
						ADDAREA(2,0,3,1,BA_18);				\
						ADDAREA(3,0,4,1,BA_19);				\
						ADDAREA(4,0,5,1,BA_20);				\
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
	//
	RT_TEST,
	RT_UNKNOWN,			// 未知角色 
}; // end enum RoleType 
#define CASERETURN(m) case m:return #m;
inline const char* convertRoleType(RoleType r){
	switch(r){
		CASERETURN(RT_GOALKEEPER);
		CASERETURN(PT_ATTACK);
		CASERETURN(PT_VANGUARD_TOP);
		CASERETURN(PT_VANGUARD_BOTTOM);
		CASERETURN(PT_ATTACK_DEFEND);
		CASERETURN(PT_DEFEND_LEFT_TOP);
		CASERETURN(PT_DEFEND_LEFT_BOT);
		CASERETURN(PT_DEFEND_RIGHT_TOP);
		CASERETURN(PF_DEFEND_RIGHT_BOT);
		CASERETURN(RT_UNKNOWN);
	}
	cout<<r;
	return "ErrorRoleType";
}

// 
// 队形编号 - 只是用来方便记忆和描述 
// 
 enum TeamNumber 
{ 
	TN_ATTACK,		// 进攻队形 
	TN_DEFEND,		// 防守队形 
	TT_TEST,		//for test
}; // end enum Team 
// 
// 记录上一次分配的角色与对应的机器人 
// 
struct LastRole 
{ 
	LastRole (void) 
	{ 
		init();
	} 
	void init(){
		for (int i = 0; i<PLAYERS_PER_SIDE; ++i) 
			role[i] = RoleType::RT_UNKNOWN; 
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

//BallField analyseFieldInfo (double x = -1.0); 

/** 
* 跟据比赛实际情况转换坐标，转换为从左向右进攻 
*/ 
//void  

/** 
* 跟据比赛实际情况转换坐标，转换为从左向右进攻 
*/ 
//void  

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

	for (long i = 0; i < PLAYERS_PER_SIDE; ++i) { 
		robotX = robots[i].pos.x; 
		robotY = robots[i].pos.y; 



		/*if (robotX > curX) { 
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
		*/
		// 
		// 获得距离 
		// 
		double tempDistance = getDistance (curX, curY, robotX, robotY); 
		if (i == 0) { 
			distance = tempDistance; 
		}else { 
			if (distance > tempDistance) { 
				distance = tempDistance; 
				index = i; 
			} 
		} 
	} 
} 
//new adding...
typedef struct 
{ 
	double x, y, z;											// 因是平面游戏,所以只用到了 x,y  
} Vector3D; 

//区域范围定义 
//##ModelId=440D001A01A5 
typedef struct 
{ 
	long left,												// 左边界  
		right,												// 右边界 
		top,												// 上边界 
		bottom;											// 下边界 
} Bounds; 
//机器人的信息定义 
//##ModelId=440D001A01D4 
#include "objects.h"


//对方机器人的信息的定义 
//##ModelId=440D001A0204 
/*typedef struct 
{ 
	Vector3D pos;											//机器人的坐标位置 
	double rotation;										//机器人当前的转角 
} OpponentRobot; */

//小球的位置定义 
//##ModelId=440D001A0223 
/**/typedef struct 
{ 
	Vector3D pos;											//小球的坐标位置 
} Ball; 

//主要的定义，包含所有运行时的的信息，由系统刷新 
//##ModelId=440D001A0251 

//#define Environment  MyEnvironment
#endif // __ROBOT_BASE_H__ 