// NewNEU.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "newneu.h"

#include "base.h"
#include "GeometryR.h"
#include "strategy.h"
#include "objects.h"

// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


// Initialize strategy
extern "C" STRATEGY_API void StrategyInit(Environment *Env) {
	Env->pointer = reinterpret_cast<long>(new StrategyBasis());
}

// Main interface function
extern "C" STRATEGY_API void StrategyStep(Environment *Env) {
	//declare some basic variables:
	const int objectsteamType = 11;
	static Object objects[objectsteamType];
	static GameState gameState;
	static StrategyBasis *strategy_pointer;
	//***********start obtain all moveable objects's inforamtion**************
	//Update my robots' data
	objects[0].setNewPosition(Env->home0_pos_x, Env->home0_pos_y);
	objects[0].setTheta(Env->home0_rotation / 180.0 * PI);
	objects[1].setNewPosition(Env->home1_pos_x, Env->home1_pos_y);
	objects[1].setTheta(Env->home1_rotation / 180.0 * PI);
	objects[2].setNewPosition(Env->home2_pos_x, Env->home2_pos_y);
	objects[2].setTheta(Env->home2_rotation / 180.0 * PI);
	objects[3].setNewPosition(Env->home3_pos_x, Env->home3_pos_y);
	objects[3].setTheta(Env->home3_rotation / 180.0 * PI);
	objects[4].setNewPosition(Env->home4_pos_x, Env->home4_pos_y);
	objects[4].setTheta(Env->home4_rotation / 180.0 * PI);
	// Update opponent robots' data
	objects[5].setNewPosition(Env->opponent0_pos_x, Env->opponent0_pos_y);
	objects[5].setTheta(Env->opponent0_rotation / 180.0 * PI);
	objects[6].setNewPosition(Env->opponent1_pos_x, Env->opponent1_pos_y);
	objects[6].setTheta(Env->opponent1_rotation / 180.0 * PI);
	objects[7].setNewPosition(Env->opponent2_pos_x, Env->opponent2_pos_y);
	objects[7].setTheta(Env->opponent2_rotation / 180.0 * PI);
	objects[8].setNewPosition(Env->opponent3_pos_x, Env->opponent3_pos_y);
	objects[8].setTheta(Env->opponent3_rotation / 180.0 * PI);
	objects[9].setNewPosition(Env->opponent4_pos_x, Env->opponent4_pos_y);
	objects[9].setTheta(Env->opponent4_rotation / 180.0 * PI);   
	// Update ball information
	objects[10].setNewPosition(Env->currentBall_pos_x, Env->currentBall_pos_y);
	objects[10].setTheta(0.0);
	//*******************end  obtain all moveable objects's inforamtion**************

	
	// Update game's state information
	gameState.myField=(BallField)Env->halfArea;
	gameState.matchState=(MatchState)Env->kickOffStyle;
	gameState.ballOwner=(BallOwner)Env->whoseBall;


	// Process strategy
	strategy_pointer = reinterpret_cast<StrategyBasis *>(Env->pointer);
	strategy_pointer->setGameState(gameState);
	strategy_pointer->Start(objects);

	// Return decision by deliver robots' wheels velocities
	Env->home0_velocityLeft =strategy_pointer->getRobot(0).getLeftVelocity();
	Env->home0_velocityRight =strategy_pointer->getRobot(0).getRightVelocity();
	Env->home1_velocityLeft =strategy_pointer->getRobot(1).getLeftVelocity();
	Env->home1_velocityRight =strategy_pointer->getRobot(1).getRightVelocity();
	Env->home2_velocityLeft =strategy_pointer->getRobot(2).getLeftVelocity();
	Env->home2_velocityRight =strategy_pointer->getRobot(2).getRightVelocity();
	Env->home3_velocityLeft =strategy_pointer->getRobot(3).getLeftVelocity();
	Env->home3_velocityRight =strategy_pointer->getRobot(3).getRightVelocity();
	Env->home4_velocityLeft =strategy_pointer->getRobot(4).getLeftVelocity();
	Env->home4_velocityRight =strategy_pointer->getRobot(4).getRightVelocity();

	// Maintain match state, since the platform will only change it if necessary
	Env->kickOffStyle = strategy_pointer->getGameState().matchState;			   
}

// Free the strategy instance
extern "C" STRATEGY_API void StrategyDrop(Environment *Env) {
	if (NULL != Env->pointer) {
		delete reinterpret_cast<StrategyBasis *>(Env->pointer);
	}
	Env->pointer = NULL;
}

// Set your team name here
extern "C" STRATEGY_API void Author(char *team) {
	strcpy(team,"Eric");
}

// Temporarily useless
extern "C" STRATEGY_API void SetForm(Environment *Env) {
}
