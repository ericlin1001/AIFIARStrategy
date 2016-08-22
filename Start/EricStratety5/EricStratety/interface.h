#ifndef __INTERFACE_H__
#define __INTERFACE_H__

// Interface of the platform
struct Environment {
    double	home0_pos_x;
    double	home0_pos_y;
    double	home0_rotation;
    double	home0_velocityLeft;
    double	home0_velocityRight;

    double	home1_pos_x;
    double	home1_pos_y;
    double	home1_rotation;
    double	home1_velocityLeft;
    double	home1_velocityRight;

    double	home2_pos_x;
    double	home2_pos_y;
    double	home2_rotation;
    double	home2_velocityLeft;
    double	home2_velocityRight;

    double	home3_pos_x;
    double	home3_pos_y;
    double	home3_rotation;
    double	home3_velocityLeft;
    double	home3_velocityRight;

    double	home4_pos_x;
    double	home4_pos_y;
    double	home4_rotation;
    double	home4_velocityLeft;
    double	home4_velocityRight;

    double	opponent0_pos_x;
    double	opponent0_pos_y;
    double	opponent0_rotation;

    double	opponent1_pos_x;
    double	opponent1_pos_y;
    double	opponent1_rotation;

    double	opponent2_pos_x;
    double	opponent2_pos_y;
    double	opponent2_rotation;

    double	opponent3_pos_x;
    double	opponent3_pos_y;
    double	opponent3_rotation;

    double	opponent4_pos_x;
    double	opponent4_pos_y;
    double	opponent4_rotation;

    double	currentBall_pos_x;
    double	currentBall_pos_y;

    long	kickOffStyle;
    long	whoseBall;
	long	halfArea;

	long	pointer;

};

// Interface of Debug mode
struct DataDebug {

	double	dataDrawBallX[40];
	double	dataDrawBallY[40];
	double	dataDrawRobot0X[40];
	double	dataDrawRobot0Y[40];
	double	dataDrawRobot1X[40];
	double	dataDrawRobot1Y[40];
	double	dataDrawRobot2X[40];
	double	dataDrawRobot2Y[40];
	double	dataDrawRobot3X[40];
	double	dataDrawRobot3Y[40];
	double	dataDrawRobot4X[40];
	double	dataDrawRobot4Y[40];
	double	dataDrawRobot5X[40];
	double	dataDrawRobot5Y[40];
	double	dataDrawRobot6X[40];
	double	dataDrawRobot6Y[40];
	double	dataDrawRobot7X[40];
	double	dataDrawRobot7Y[40];
	double	dataDrawRobot8X[40];
	double	dataDrawRobot8Y[40];
	double	dataDrawRobot9X[40];
	double	dataDrawRobot9Y[40];
	double	dataDrawRobot10X[40];
	double	dataDrawRobot10Y[40];
	int		robotRole[11];

};

#define STRATEGY_API __declspec(dllexport)

/* MUST BE IMPLEMENTED */
extern "C" STRATEGY_API void StrategyInit(Environment * Env);
extern "C" STRATEGY_API void StrategyStep(Environment * Env);
extern "C" STRATEGY_API void StrategyDrop(Environment * Env);
extern "C" STRATEGY_API void Author(char * team);
extern "C" STRATEGY_API void SetForm(Environment * Env);
//extern "C" STRATEGY_API void StrategyStepDebug(Environment * Env, DataDebug * Data);
#endif  // NEWNEU_ROBOT_SOCCER_09S_INTERFACE_H_
