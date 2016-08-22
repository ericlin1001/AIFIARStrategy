// NewNEU.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"


#include "interface.h"
#include "objects.h"
#include "base.h"
#include "MyStrategy.h"


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
  Env->pointer = reinterpret_cast<long>(new Strategy());
}

// Main interface function
extern "C" STRATEGY_API void StrategyStep(Environment *Env) {
  // Gird copy of robots and ball's data
  const int objects_number = 11;
  static Object objects[objects_number];

  // Update home robots' data
  objects[0].set_vector(Env->home0_pos_x - objects[0].get_position().GetX(),
                        Env->home0_pos_y - objects[0].get_position().GetY());
  objects[0].set_position(Env->home0_pos_x, Env->home0_pos_y);
  objects[0].set_theta(Env->home0_rotation / 180.0 * PI);

  objects[1].set_vector(Env->home1_pos_x - objects[1].get_position().GetX(),
                        Env->home1_pos_y - objects[1].get_position().GetY());
  objects[1].set_position(Env->home1_pos_x, Env->home1_pos_y);
  objects[1].set_theta(Env->home1_rotation / 180.0 * PI);

  objects[2].set_vector(Env->home2_pos_x - objects[2].get_position().GetX(),
                        Env->home2_pos_y - objects[2].get_position().GetY());
  objects[2].set_position(Env->home2_pos_x, Env->home2_pos_y);
  objects[2].set_theta(Env->home2_rotation / 180.0 * PI);

  objects[3].set_vector(Env->home3_pos_x - objects[3].get_position().GetX(),
                        Env->home3_pos_y - objects[3].get_position().GetY());
  objects[3].set_position(Env->home3_pos_x, Env->home3_pos_y);
  objects[3].set_theta(Env->home3_rotation / 180.0 * PI);

  objects[4].set_vector(Env->home4_pos_x - objects[4].get_position().GetX(),
                        Env->home4_pos_y - objects[4].get_position().GetY());
  objects[4].set_position(Env->home4_pos_x, Env->home4_pos_y);
  objects[4].set_theta(Env->home4_rotation / 180.0 * PI);

  // Update opponent robots' data
  objects[5].set_vector(Env->opponent0_pos_x - objects[5].get_position().GetX(),
                        Env->opponent0_pos_y - objects[5].get_position().GetY());
  objects[5].set_position(Env->opponent0_pos_x, Env->opponent0_pos_y);
  objects[5].set_theta(Env->opponent0_rotation / 180.0 * PI);

  objects[6].set_vector(Env->opponent1_pos_x - objects[6].get_position().GetX(),
                        Env->opponent1_pos_y - objects[6].get_position().GetY());
  objects[6].set_position(Env->opponent1_pos_x, Env->opponent1_pos_y);
  objects[6].set_theta(Env->opponent1_rotation / 180.0 * PI);

  objects[7].set_vector(Env->opponent2_pos_x - objects[7].get_position().GetX(),
                        Env->opponent2_pos_y - objects[7].get_position().GetY());
  objects[7].set_position(Env->opponent2_pos_x, Env->opponent2_pos_y);
  objects[7].set_theta(Env->opponent2_rotation / 180.0 * PI);

  objects[8].set_vector(Env->opponent3_pos_x - objects[8].get_position().GetX(),
                        Env->opponent3_pos_y - objects[8].get_position().GetY());
  objects[8].set_position(Env->opponent3_pos_x, Env->opponent3_pos_y);
  objects[8].set_theta(Env->opponent3_rotation / 180.0 * PI);

  objects[9].set_vector(Env->opponent4_pos_x - objects[9].get_position().GetX(),
                        Env->opponent4_pos_y - objects[9].get_position().GetY());
  objects[9].set_position(Env->opponent4_pos_x, Env->opponent4_pos_y);
  objects[9].set_theta(Env->opponent4_rotation / 180.0 * PI);   

  // Update ball information
  objects[10].set_vector(Env->currentBall_pos_x - objects[10].get_position().GetX(),
                        Env->currentBall_pos_y - objects[10].get_position().GetY());
  objects[10].set_position(Env->currentBall_pos_x, Env->currentBall_pos_y);
  objects[10].set_theta(0.0);  // Ball's direction is always 0
  
  // If the positions of objects have been reset(in most case caused by the 
  // change of the match state), all objects' displacements will be set to be 0.
  if (Env->kickOffStyle != MatchState::MS_UNDER_WAY) {
    
  }

  // Update match information
  static GameState gs;
  gs.myField=(BallField)Env->halfArea;
  gs.matchState=(MatchState)Env->kickOffStyle;
  gs.ballOwner=(BallOwner)Env->whoseBall;
  //
  if(gs.matchState==MatchState::MS_UNDER_WAY){
	 for (int i = 0; i < objects_number; ++i) {
      objects[i].set_vector(0.0, 0.0);
    }
  }
  // TODO: Maybe you should add something to deal with the penalty situation
  //       nDEPenaltyDirection is not set.

  // Process strategy
  static Strategy *strategy_pointer;
  strategy_pointer = reinterpret_cast<Strategy *>(Env->pointer);
  strategy_pointer->set_gs(gs);
  strategy_pointer->Start(objects);
  
  // Return decision by deliver robots' wheels velocities
  Env->home0_velocityLeft = 
      strategy_pointer->get_robot(0).get_left_velocity();
  Env->home0_velocityRight = 
      strategy_pointer->get_robot(0).get_right_velocity();

  Env->home1_velocityLeft = 
      strategy_pointer->get_robot(1).get_left_velocity();
  Env->home1_velocityRight = 
      strategy_pointer->get_robot(1).get_right_velocity();

  Env->home2_velocityLeft = 
      strategy_pointer->get_robot(2).get_left_velocity();
  Env->home2_velocityRight = 
      strategy_pointer->get_robot(2).get_right_velocity();

  Env->home3_velocityLeft = 
      strategy_pointer->get_robot(3).get_left_velocity();
  Env->home3_velocityRight = 
      strategy_pointer->get_robot(3).get_right_velocity();
  
  Env->home4_velocityLeft = 
      strategy_pointer->get_robot(4).get_left_velocity();
  Env->home4_velocityRight =
      strategy_pointer->get_robot(4).get_right_velocity();

  // Maintain match state, since the platform will only change it if necessary
  Env->kickOffStyle = strategy_pointer->get_gs().matchState;					   
}

// Free the strategy instance
extern "C" STRATEGY_API void StrategyDrop(Environment *Env) {
  if (NULL != Env->pointer) {
    delete reinterpret_cast<Strategy *>(Env->pointer);
  }
  Env->pointer = NULL;
}

// Set your team name here
extern "C" STRATEGY_API void Author(char *team) {
  strcpy(team,"Eric");
}

// Temporarily useless
extern "C" STRATEGY_API void SetForm(Environment *Env) {}

/*
// Debug version interface
extern "C" STRATEGY_API void StrategyStepDebug(Environment *Env, DataDebug *Data) {
  StrategyStep(Env);
  StrategyBasis *strategy_pointer = reinterpret_cast<StrategyBasis *>(Env->pointer);
  *Data = strategy_pointer->get_debugdata();
}

*/