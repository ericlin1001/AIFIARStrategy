#ifndef Strategy_H
#define Strategy_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STRATEGY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STRATEGY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef STRATEGY_EXPORTS
#define STRATEGY_API __declspec(dllexport)
#else
#define STRATEGY_API __declspec(dllimport)
#endif



// kickOffStyle
const long Normal=0;
const long FREE_BALL = 1;//����
const long PENALTY_KICK = 2;
const long FREE_KICK = 3;//������
const long GOAL_KICK = 4;//����

// whoseBall
const long ANYONES_BALL = 0;/*0���⣬1��������2�Է�����*/
const long BLUE_BALL = 1;
const long YELLOW_BALL = 2;
//halfArea
const long LeftArea=0;/*��0��볡�ƶӣ�1�Ұ볡���ӣ���*/
const long RightArea=1;

typedef struct
{
    double home0_pos_x;
    double home0_pos_y;
    double home0_rotation;/*�������������������ļнǣ���ʱ��Ϊ����ȡֵ��ΧΪ(-180,180]��*/
    double home0_velocityLeft;/*[-100,100]����λ��rad/s��*/
    double home0_velocityRight;

    double home1_pos_x;
    double home1_pos_y;
    double home1_rotation;
    double home1_velocityLeft;
    double home1_velocityRight;

    double home2_pos_x;
    double home2_pos_y;
    double home2_rotation;
    double home2_velocityLeft;
    double home2_velocityRight;

    double home3_pos_x;
    double home3_pos_y;
    double home3_rotation;
    double home3_velocityLeft;
    double home3_velocityRight;

    double home4_pos_x;
    double home4_pos_y;
    double home4_rotation;
    double home4_velocityLeft;
    double home4_velocityRight;

    double opponent0_pos_x;
    double opponent0_pos_y;
    double opponent0_rotation;

    double opponent1_pos_x;
    double opponent1_pos_y;
    double opponent1_rotation;

    double opponent2_pos_x;
    double opponent2_pos_y;
    double opponent2_rotation;

    double opponent3_pos_x;
    double opponent3_pos_y;
    double opponent3_rotation;

    double opponent4_pos_x;
    double opponent4_pos_y;
    double opponent4_rotation;

    double currentBall_pos_x;
    double currentBall_pos_y;
	//
    long kickOffStyle;
    long whoseBall;
	long halfArea;

	long pointer;
} Environment;

typedef void (*MyStrategyProc)(Environment*);

/* MUST BE IMPLEMENTED */
extern "C" STRATEGY_API void StrategyInit(Environment* Env);
extern "C" STRATEGY_API void StrategyStep(Environment* Env);
extern "C" STRATEGY_API void StrategyDrop(Environment* Env);
extern "C" STRATEGY_API void Author(char* team);
extern "C" STRATEGY_API void SetForm(Environment* Env);

#endif // Strategy_H