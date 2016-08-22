/**************************************************************************************************** 
base.h 
 
Purpose: 
	����������������� ״̬��Ϣö����,���÷��� 
****************************************************************************************************/ 
#ifndef __BASE_H__ 
#define __BASE_H__ 
 
#include <afxcom_.h> 
#include <math.h> 
#include <algorithm> 
#include <vector> 
using namespace std; 
/***********************************
������λ�趨:
����:g
·��:cm
		
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
�����ھ���ʱ,�Ὣ�ҷ�ת��Ϊ�������ҷ�����,
�����������Ϣ�����ҷ�Ϊ��Ϊ��!
************************************/
const long PLAYERS_PER_SIDE = 5;	

namespace BALL_INFO{
const double WEIGHT=46;//g
const double DIAMETER=4.27;//cm
const double RADIUS=DIAMETER/2;
};

namespace ROBOT_INIFO{
const double LENGTH=7.5;//xlen
//const double WIDTH=7.5;//ylen
const double HEIGHT=4.5;
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
	inline double getOppCenterX(){return FIELD_INFO::LENGTH+ROBOT_INIFO::LENGTH;}
	inline double getOppCenterY(){return FIELD_INFO::getCenterY();}
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

// �ҷ����ڵ��򳡷��� 
enum BallField{
	BF_LEFT= 0, 
	BF_RIGHT=1 
};
// ����״̬ 
enum Match_State{ 
	MS_NORMAL = 0, //��������
	MS_FREE_BALL = 1, // ���������� 
	MS_PENALTY_KICK = 2,// ����
	MS_FREE_KICK = 3, // ������ 
	MS_GOAL_KICK = 4, // ���� 
	MS_UNDER_WAY = 5,//������
};
// ����
enum BallOwner{
	BO_ANYONE=0,
	BO_SELF=1,
	BO_OPP=2,
};


//enum PenaltyState{ DEFENSE = 0, ATTACK = 1 };


// 
// �ҷ�����ԱĬ��λ�� 
// 
/*
const double GOAL_CENTER_X = FLEFTX + ROBOT_DIAMETER / 3;		// ���ŵ����ĵ� X + ���������λ�� 
const double GOAL_CENTER_Y = FIELD_CENTER_Y;					// ���ŵ����ĵ� Y λ�� 
 
const double ATTACK_DEFEND_X = FLEFTX + FIELD_WIDTH / 4;		// ����������Ĭ�� X 
const double ATTACK_DEFEND_Y = FIELD_CENTER_Y;					// ����������Ĭ�� Y 
 
// 
// �ҷ�����λ�� 
// 
const double DEFEND_TOP_X = 37.2016;							// X 
 
const double DEFEND_LEFT_TOP_X = 17.6934;						// ���Ϻ�����Ĭ��λ�� 
const double DEFEND_LEFT_TOP_Y = 58.5660; 
 
const double DEFEND_LEFT_BOT_X = DEFEND_LEFT_TOP_X;				// ���º�����Ĭ��λ�� 
const double DEFEND_LEFT_BOT_Y = 27.8966; 
 
const double DEFEND_RIGHT_TOP_X = 27.8173;						// ���Ϻ���Ĭ��λ�� 
const double DEFEND_RIGHT_TOP_Y = 66.2858; 
 
const double DEFEND_RIGHT_BOT_X = 27.8173;						// ���º���Ĭ��λ�� 
const double DEFEND_RIGHT_BOT_Y = 19.9442; 
 */
// 

// 
// �������ϵ����� 
// 
enum BallArea 
{ 
	BA_UNKNOWN,				// δ֪���� 
	BA_1, BA_2, BA_3, BA_4, BA_5, 
	BA_6, BA_7, BA_8, BA_9, BA_10, 
	BA_11, BA_12, BA_13, BA_14, BA_15, 
	BA_16, BA_17, BA_18, BA_19, BA_20, 
}; // end enum BallArea 
 
// 
// ����ٶ���Ϣ 
// 
enum BallSpeed 
{ 
	BS_UNKNOWN,				// δ֪�ٶ� 
	BS_LOW,					// ���� 
	BS_MIDDLE_LOW,			// �е��� 
	BS_MIDDLE,				// ���� 
	BS_HIGH,				// ���� 
	BS_MORE_HIGH,			// ����� 
}; // end enum BallSpeed 
 
// 
// ����˶����� 
// 
enum BallDirection 
{ 
	BD_UNKNOWN,				// δ֪���� 
	BD_REST,				// ��ֹ 
	BD_RIGHT,				// �� 
	BD_RIGHT_TOP,			// ���� 
	BD_TOP,					// �� 
	BD_LEFT_TOP,			// ���� 
	BD_LEFT,				// �� 
	BD_LEFT_BOTTOM,			// ���� 
	BD_BOTTOM,				// �� 
	BD_RIGHT_BOTTOM,		// ���� 
}; // end enum BallDirection 
 
// 
// ��Ŀ���Ȩ 
// 
enum BallPower 
{ 
	BP_UNKNOWN,				// δ֪״̬ 
	BP_OPPONENT,			// �з����� 
	BP_CONFRONT,			// ˫����ţ������ 
	BP_SELF,				// �ҷ����� 
	BP_WITHOUT,				// ˫���Բ����� 
}; // enum BallPower 
 
// 
// ����©�� 
// 
enum GuardLeak 
{ 
	GL_UNKNOWN,				// δ֪״̬ 
	GL_OPPONENT_MORE_BIG,	// �з�©���ܴ� 
	GL_OPPONENT_BIG,		// �з�©���� 
	GL_OPPONENT_SMALL,		// �з�©��С 

	GL_SELF_SMALL,			// �ҷ�©��С 
	GL_SELF_BIG,			// �ҷ�©���� 
	GL_SELF_MORE_BIG,		// �ҷ�©���ܴ� 
}; // end enum GuardLeak 
 
// 
// �����˽�ɫ���� 
// 
enum RoleType 
{ 
	RT_GOALKEEPER,		// ����Ա��ɫ 
 
	// 
	// �����ͽ�ɫ 
	// 
	RT_ATTACK,			// ������ - ������·�ȴ���ϲ����� 
	RT_VANGUARD_TOP,	// ��ǰ�� - ����ʱ�����ϰ���� 
	RT_VANGUARD_BOTTOM,	// ��ǰ�� - ����ʱ�����°���� 
	RT_ATTACK_DEFEND,	// �������� - ѡ���������ʱ������صĻ����� 
 
	// 
	// �����ͽ�ɫ 
	// 
	RT_DEFEND_LEFT_TOP,	// ���Ͻǵĺ��� 
	RT_DEFEND_LEFT_BOT,	// ���½ǵĺ��� 
	RT_DEFEND_RIGHT_TOP,// ���Ͻǵĺ��� 
	RT_DEFEND_RIGHT_BOT,// ���½ǵĺ��� 
 
/* 
	RT_POINT_BALL,		// �����ɫ 
	PT_DOOR_BALL,		// �����ɫ 
	PT_CONTEST_BALL,	// �����ɫ 
	PT_FREE_KICK,		// �������ɫ 
 
	PT_SHOOT,			// ���Ž�ɫ - ��·����·...���Ž�ɫ����ʱ�䲻����ʱ��ϸ�� 
	PT_REPAIR,			// �����ɫ - ��·����... 
*/ 
	RT_UNKNOWN,			// δ֪��ɫ 
}; // end enum RoleType 
 
// 
// ���α�� - ֻ������������������ 
// 
enum TeamType 
{ 
	TT_ATTACK,		// �������� 
	TT_DEFEND,		// ���ض��� 
};
 
// 
// ��¼��һ�η���Ľ�ɫ���Ӧ�Ļ����� 
// 
struct LastRole 
{ 
	LastRole (void) 
	{ 
		for (int i = 0; i<PLAYERS_PER_SIDE; ++i) 
			role[i] = RoleType::RT_UNKNOWN; 
	} 
 
	// 
	// ����ֵ��Ӧ��Ϊ������������ 
	// �� role[0] == RT_UNKNOWN ��Ϊ ������ 0 ��һ�η���Ľ�ɫΪδ֪��ɫ 
	// 
	RoleType role[PLAYERS_PER_SIDE]; 
}; // struct LastRole 
 
// 
// ɾ�� 
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
 * ���ݸ����� x λ�÷���������Ϣ 
 * �� Strategy �������ʼ������ 
 */ 

BallField analyseFieldInfo (double x = -1.0); 
 
/** 
 * ���ݱ���ʵ�����ת�����꣬ת��Ϊ�������ҽ��� 
 */ 
void transform (double &x, double &y); 
 
/** 
 * ���ݱ���ʵ�����ת�����꣬ת��Ϊ�������ҽ��� 
 */ 
void transform (double &rotation); 
 
/** 
 * �� pointX, pointY �Ƿ��� 
 * �� topX, topY - topX, topY �������� 
 * ������������ topY > botY 
 */ 
bool isComprise (double topX, double topY, double botX, double botY, double pointX, double pointY); 
 
/** 
 * �������֮��ľ��� 
 */ 
double getDistance (double x1, double y1, double x2, double y2); 
 
/** 
 * ��ø�������֮��ĽǶ��γɵ�ֱ��ӳ�䵽������ X �㴦�ĸ߶Ⱦ��� 
 * x1, y1 -> # 
 * x2, y2 -> @ 
 * targetX, targetY -> (*) 
 */ 
double getMappedTargetY (double x1, double y1, double x2, double y2, double targetX); 
 
/** 
 * ��������������Ա����Լ����� 
 */ 
template<typename T> 
void getVicinityPoint (const T *robots, double curX, double curY, long &index, double &distance) 
{ 
	/* 
		��Ա�����λ����������� 
	 
		+-----------------+ 
		+    1      2     + 
		+       []        + 
		+    3      4     + 
		+-----------------+ 
	 
		1. ((curX - ��Ա.x)^2 + (��Ա.y - curY)^2)~2 
		2. ((��Ա.x - curX)^2 + (��Ա.y - curY)^2)~2 
		3. ((curX - ��Ա.x)^2 + (curY - ��Ա.y)^2)~2 
		4. ((��Ա.x - curX)^2 + (curY - ��Ա.y)^2)~2 
	 
		((maxX - minX)^2 + (maxY - minY)^2)~2 
	*/ 
	 
	double robotX = 0; 
	double robotY = 0; 
 
	double maxX = 0; 
	double minX = 0; 
 
	double maxY = 0; 
	double minY = 0; 
 
	index = 0;			// ��¼��������Ķ�Ա 
	distance = 0;		// ��̾��� 
 
	for (long i = 0; i <PLAYERS_PER_SIDE; ++i) { 
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
		// ��þ��� 
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