/**************************************************************************************************** 
base.h 
 
Purpose: 
	艾数机器人足球策略 状态信息枚举体,公用方法 
****************************************************************************************************/ 
#ifndef __BASE_H__ 
#define __BASE_H__ 
 
#define DEBUG
#ifdef DEBUG
#include <iostream>
using namespace std;
#define Show(m) cout<<m<<endl;
#else 
#define Show(m)
#endif




//#include <afxcom_.h> 
#include <math.h> 
#include <algorithm> 
#include <vector> 
using namespace std; 
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
#define ASSERT(m) 
const int PLAYERS_PER_SIDE = 5;	

namespace BALL_INFO{
const double WEIGHT=46;//g
const double DIAMETER=4.27;//cm
const double RADIUS=DIAMETER/2;
};

namespace ROBOT_INFO{
const double LENGTH=7.5;//xlen
const double HALF_LENGTH=LENGTH/2;
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
const double GOAL_CENTER_X = 0 + ROBOT_INFO::LENGTH / 3;		// 球门的中心点 X + 半个机器人位置 
const double GOAL_CENTER_Y = FIELD_INFO::getCenterY();			// 球门的中心点 Y 位置 
 
const double ATTACK_DEFEND_X = 0 + FIELD_INFO::LENGTH / 4;		// 进攻后卫的默认 X 
const double ATTACK_DEFEND_Y = FIELD_INFO::getCenterY();		// 进攻后卫的默认 Y 
 
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

const double FLEFTX      = 6.8118;							// 场地左边界 
const double FTOP        = 77.2392;							// 场地上边界 
const double FRIGHTX     = 93.4259;							// 场地右边界 
const double FBOT        = 6.3730;							// 场地下边界 
 
const double GRIGHT      = 97.3632;							// 球门右边界 
const double GLEFT       = 2.8748;							// 球门左边界 
const double GTOPY       = 49.6801;							// 球门上边界 
const double GBOTY       = 33.9320;							// 球门下边界 

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
	RT_ATTACK,			// 进攻者 - 负责中路等待配合并进攻 
	RT_VANGUARD_TOP,	// 上前锋 - 进攻时负责上半个球场 
	RT_VANGUARD_BOTTOM,	// 下前锋 - 进攻时负责下半个球场 
	RT_ATTACK_DEFEND,	// 进攻后卫 - 选择进攻队形时负责防守的机器人 
 
	// 
	// 防守型角色 
	// 
	RT_DEFEND_LEFT_TOP,	// 左上角的后卫 
	RT_DEFEND_LEFT_BOT,	// 左下角的后卫 
	RT_DEFEND_RIGHT_TOP,// 右上角的后卫 
	RT_DEFEND_RIGHT_BOT,// 右下角的后卫 
 
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


char *getRoleTypeName(RoleType t);
// 
// 队形编号 - 只是用来方便记忆和描述 
// 
enum TeamType 
{ 
	TT_ATTACK,		// 进攻队形 
	TT_DEFEND,		// 防守队形 
};
 
// 
// 记录上一次分配的角色与对应的机器人 
// 
struct LastRole 
{ 
	LastRole (void) 
	{ 
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
#endif // __ROBOT_BASE_H__ 