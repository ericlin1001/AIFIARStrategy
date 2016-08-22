/**************************************************************************************************** 
base.h 

Purpose: 
����������������� ״̬��Ϣö����,���÷��� 
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

// �ҷ����ڵ��򳡷��� 
enum BallField{
	LEFT= 0, 
	RIGHT=1 
};
// ����״̬ 
enum MatchState{ 
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
struct GameState{
	BallField myField;
	MatchState matchState;
	BallOwner ballOwner;
};

//enum PenaltyState{ DEFENSE = 0, ATTACK = 1 };


// 
// �ҷ�����ԱĬ��λ�� 
// 
const double GOAL_CENTER_X = 0 + ROBOT_INFO::LENGTH / 2;		// ���ŵ����ĵ� X + ���������λ�� 
const double GOAL_CENTER_Y = FIELD_INFO::getCenterY();			// ���ŵ����ĵ� Y λ�� 

const double ATTACK_DEFEND_X = 0 + FIELD_INFO::LENGTH / 4;		// ����������Ĭ�� X 
const double ATTACK_DEFEND_Y = FIELD_INFO::getCenterY();		// ����������Ĭ�� Y 

// 
// �ҷ�����λ�� 
// 
const double DEFEND_TOP_X = FIELD_INFO::LENGTH/4*3/4;							// X 

const double DEFEND_LEFT_TOP_X = FIELD_INFO::LENGTH/4*7/10;						// ���Ϻ�����Ĭ��λ�� 
const double DEFEND_LEFT_TOP_Y = 120; 

const double DEFEND_LEFT_BOT_X = DEFEND_LEFT_TOP_X;				// ���º�����Ĭ��λ�� 
const double DEFEND_LEFT_BOT_Y = FIELD_INFO::WIDTH-DEFEND_LEFT_TOP_Y; 

const double DEFEND_RIGHT_TOP_X = FIELD_INFO::LENGTH/4*13/10;						// ���Ϻ���Ĭ��λ�� 
const double DEFEND_RIGHT_TOP_Y = 110; 

const double DEFEND_RIGHT_BOT_X = DEFEND_RIGHT_TOP_X;						// ���º���Ĭ��λ�� 
const double DEFEND_RIGHT_BOT_Y = FIELD_INFO::WIDTH-DEFEND_RIGHT_TOP_Y; 

// 
const double EDGE		 = BALL_INFO::RADIUS;
const double FLEFTX      = EDGE;							// ������߽� 
const double FTOP        = FIELD_INFO::WIDTH-EDGE;							// �����ϱ߽� 
const double FRIGHTX     = FIELD_INFO::LENGTH-EDGE;							// �����ұ߽� 
const double FBOT        = EDGE;							// �����±߽� 

const double GRIGHT      = FIELD_INFO::GOAL::getOppCenterX();							// �����ұ߽� 
const double GLEFT       = 2.8748;							// ������߽� 
const double GTOPY       = FIELD_INFO::GOAL::getOppCenterY()+FIELD_INFO::GOAL::WIDTH/2;							// �����ϱ߽� 
const double GBOTY       = FIELD_INFO::GOAL::getOppCenterY()-FIELD_INFO::GOAL::WIDTH/2;							// �����±߽� 
//******************************
const double BALL_DIAMETER = BALL_INFO::DIAMETER;							// ���ֱ�� 
const double ROBOT_DIAMETER = ROBOT_INFO::LENGTH;							// �����˵�ֱ�� 
 
const double FIELD_WIDTH = FIELD_INFO::LENGTH;					// �򳡿� 
const double FIELD_HEIGHT = FIELD_INFO::WIDTH;						// �򳡸� 
 
const double FIELD_CENTER_Y = FIELD_INFO::getCenterY();			// �򳡵�����λ�� Y 
const double FIELD_CENTER_X = FIELD_INFO::getCenterX();			// �򳡵�����λ�� Y 
  

const double FORBIDDEN_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getX();//19.8003;						// �ҷ����� X ���� 
 
const double OPP_GOAL_CENTER_X = FRIGHTX + ROBOT_DIAMETER;		// �Է��������ĵ㣬�Է��򳡱��� + 1��������λ�� 
const double OPP_GOAL_CENTER_Y = FIELD_CENTER_Y;				// �Է����ŵ����ĵ� Y λ�� 
const double OPP_SMALL_FORBID_ZONE_X = FIELD_INFO::GOAL_AREA::getOppX();					// �Է�С������ X ���� 
 
const double SMALL_FORBID_ZONE_TOPY = FIELD_INFO::GOAL_AREA::getTop();					// С�����ϱ߽� 
const double SMALL_FORBID_ZONE_BOTY = FIELD_INFO::GOAL_AREA::getBot();					// С�����±߽� 
const double SMALL_FORBID_ZONE_X = FIELD_INFO::GOAL_AREA::getX();						// �ҷ�С������ X ���� 
 
const double FORBID_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getX();							// �ҷ����� X ���� 
const double OPP_FORBID_ZONE_X = FIELD_INFO::FORBIDDEN_AREA::getOppX();						// �Է����� X ���� 
 
//********************************
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
	PT_ATTACK,			// ������ - ������·�ȴ���ϲ����� 
	PT_VANGUARD_TOP,	// ��ǰ�� - ����ʱ�����ϰ���� 
	PT_VANGUARD_BOTTOM,	// ��ǰ�� - ����ʱ�����°���� 
	PT_ATTACK_DEFEND,	// �������� - ѡ���������ʱ������صĻ����� 

	// 
	// �����ͽ�ɫ 
	// 
	PT_DEFEND_LEFT_TOP,	// ���Ͻǵĺ��� 
	PT_DEFEND_LEFT_BOT,	// ���½ǵĺ��� 
	PT_DEFEND_RIGHT_TOP,// ���Ͻǵĺ��� 
	PF_DEFEND_RIGHT_BOT,// ���½ǵĺ��� 

	/* 
	RT_POINT_BALL,		// �����ɫ 
	PT_DOOR_BALL,		// �����ɫ 
	PT_CONTEST_BALL,	// �����ɫ 
	PT_FREE_KICK,		// �������ɫ 

	PT_SHOOT,			// ���Ž�ɫ - ��·����·...���Ž�ɫ����ʱ�䲻����ʱ��ϸ�� 
	PT_REPAIR,			// �����ɫ - ��·����... 
	*/ 
	//
	RT_TEST,
	RT_UNKNOWN,			// δ֪��ɫ 
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
// ���α�� - ֻ������������������ 
// 
 enum TeamNumber 
{ 
	TN_ATTACK,		// �������� 
	TN_DEFEND,		// ���ض��� 
	TT_TEST,		//for test
}; // end enum Team 
// 
// ��¼��һ�η���Ľ�ɫ���Ӧ�Ļ����� 
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

//BallField analyseFieldInfo (double x = -1.0); 

/** 
* ���ݱ���ʵ�����ת�����꣬ת��Ϊ�������ҽ��� 
*/ 
//void  

/** 
* ���ݱ���ʵ�����ת�����꣬ת��Ϊ�������ҽ��� 
*/ 
//void  

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
		// ��þ��� 
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
	double x, y, z;											// ����ƽ����Ϸ,����ֻ�õ��� x,y  
} Vector3D; 

//����Χ���� 
//##ModelId=440D001A01A5 
typedef struct 
{ 
	long left,												// ��߽�  
		right,												// �ұ߽� 
		top,												// �ϱ߽� 
		bottom;											// �±߽� 
} Bounds; 
//�����˵���Ϣ���� 
//##ModelId=440D001A01D4 
#include "objects.h"


//�Է������˵���Ϣ�Ķ��� 
//##ModelId=440D001A0204 
/*typedef struct 
{ 
	Vector3D pos;											//�����˵�����λ�� 
	double rotation;										//�����˵�ǰ��ת�� 
} OpponentRobot; */

//С���λ�ö��� 
//##ModelId=440D001A0223 
/**/typedef struct 
{ 
	Vector3D pos;											//С�������λ�� 
} Ball; 

//��Ҫ�Ķ��壬������������ʱ�ĵ���Ϣ����ϵͳˢ�� 
//##ModelId=440D001A0251 

//#define Environment  MyEnvironment
#endif // __ROBOT_BASE_H__ 