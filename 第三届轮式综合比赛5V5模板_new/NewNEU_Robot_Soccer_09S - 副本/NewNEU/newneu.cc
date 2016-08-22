// NewNEU.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "newneu.h"

#include "defines.h"
#include "GeometryR.h"
#include "strategy.h"
#include "objects.h"
#include <iostream>
using namespace std;
// Initialize strategy
extern "C" STRATEGY_API void StrategyInit(Environment *Env) {
	Env->pointer = reinterpret_cast<long>(new StrategyBasis("DebugData.txt",0));
}

// Main interface function
extern "C" STRATEGY_API void StrategyStep(Environment *Env) {
	//declare some basic variables:
	const int objects_number = 11;
	static Object objects[objects_number];
	static DEGame mode;
	static StrategyBasis *strategy_pointer;
	//***********start obtain all moveable objects's inforamtion**************
	//Update my robots' data
	objects[0].set_new_position(Env->home0_pos_x, Env->home0_pos_y);
	objects[0].set_theta(Env->home0_rotation / 180.0 * PI);
	objects[1].set_new_position(Env->home1_pos_x, Env->home1_pos_y);
	objects[1].set_theta(Env->home1_rotation / 180.0 * PI);
	objects[2].set_new_position(Env->home2_pos_x, Env->home2_pos_y);
	objects[2].set_theta(Env->home2_rotation / 180.0 * PI);
	objects[3].set_new_position(Env->home3_pos_x, Env->home3_pos_y);
	objects[3].set_theta(Env->home3_rotation / 180.0 * PI);
	objects[4].set_new_position(Env->home4_pos_x, Env->home4_pos_y);
	objects[4].set_theta(Env->home4_rotation / 180.0 * PI);
	// Update opponent robots' data
	objects[5].set_new_position(Env->opponent0_pos_x, Env->opponent0_pos_y);
	objects[5].set_theta(Env->opponent0_rotation / 180.0 * PI);
	objects[6].set_new_position(Env->opponent1_pos_x, Env->opponent1_pos_y);
	objects[6].set_theta(Env->opponent1_rotation / 180.0 * PI);
	objects[7].set_new_position(Env->opponent2_pos_x, Env->opponent2_pos_y);
	objects[7].set_theta(Env->opponent2_rotation / 180.0 * PI);
	objects[8].set_new_position(Env->opponent3_pos_x, Env->opponent3_pos_y);
	objects[8].set_theta(Env->opponent3_rotation / 180.0 * PI);
	objects[9].set_new_position(Env->opponent4_pos_x, Env->opponent4_pos_y);
	objects[9].set_theta(Env->opponent4_rotation / 180.0 * PI);   
	// Update ball information
	objects[10].set_new_position(Env->currentBall_pos_x, Env->currentBall_pos_y);
	objects[10].set_theta(0.0);
	//*******************end  obtain all moveable objects's inforamtion**************

	// If the positions of objects have been reset(in most case caused by the 
	// change of the match state), all objects' displacements will be set to be 0.
	//??this also seem strange,i think this will never happen.
#define Trace(m) cout<<#m<<"="<<(m)<<endl;
	cout<<endl;
	Trace(Env->kickOffStyle);
	Trace(Env->whoseBall);
	Trace(Env->halfArea);
	
	if (Env->kickOffStyle != FieldInfo::Match_State::UNDER_WAY) {
		for (int i = 0; i < objects_number; ++i) {
			objects[i].set_vector(0.0, 0.0);
		}
	}

	// Update match information
	mode.nDEGameGround = Env->halfArea;
	mode.nDEStartMode = Env->kickOffStyle;
	if (Env->whoseBall == Env->halfArea || FieldInfo::Ball_Ownership::ANYONE == Env->whoseBall) {
		mode.nDEStartState = FieldInfo::Penalty_State::ATTACK;
	}else {
		mode.nDEStartState =  FieldInfo::Penalty_State::DEFENSE;
	}
	/* TODO: Maybe you should add something to deal with the penalty situation
	       nDEPenaltyDirection is not set.*/


	// Process strategy
	strategy_pointer = reinterpret_cast<StrategyBasis *>(Env->pointer);
	strategy_pointer->set_deg(mode);
	strategy_pointer->Start(objects);

	// Return decision by deliver robots' wheels velocities
	Env->home0_velocityLeft =strategy_pointer->get_robot(0).get_left_velocity();
	Env->home0_velocityRight =strategy_pointer->get_robot(0).get_right_velocity();
	Env->home1_velocityLeft =strategy_pointer->get_robot(1).get_left_velocity();
	Env->home1_velocityRight =strategy_pointer->get_robot(1).get_right_velocity();
	Env->home2_velocityLeft =strategy_pointer->get_robot(2).get_left_velocity();
	Env->home2_velocityRight =strategy_pointer->get_robot(2).get_right_velocity();
	Env->home3_velocityLeft =strategy_pointer->get_robot(3).get_left_velocity();
	Env->home3_velocityRight =strategy_pointer->get_robot(3).get_right_velocity();
	Env->home4_velocityLeft =strategy_pointer->get_robot(4).get_left_velocity();
	Env->home4_velocityRight =strategy_pointer->get_robot(4).get_right_velocity();

	// Maintain match state, since the platform will only change it if necessary
	Env->kickOffStyle = strategy_pointer->get_deg().nDEStartMode;					   
}

// Free the strategy instance
extern "C" STRATEGY_API void StrategyDrop(Environment *Env) {
	if (NULL != Env->pointer) {
		delete reinterpret_cast<StrategyBasis *>(Env->pointer);
	}
	Env->pointer = NULL;
}

// Set your team name here
#include<fstream>
using namespace std;
extern "C" STRATEGY_API void Author(char *team) {
#define TEAM_NAME_FILE "teamName.txt"
	char buffer[100]="Test";
	int testCount=0;
	//
	ifstream infile;
	infile.open(TEAM_NAME_FILE);
	if(!infile.fail()){
		infile>>buffer>>testCount;
	}
	infile.close();
	//
	testCount++;char countbuffer[10];
	strcpy(team,buffer);itoa(testCount,countbuffer,100);strcat(team,countbuffer);
	
	//
	ofstream outfile;
	outfile.open(TEAM_NAME_FILE);
	outfile<<buffer<<endl
		<<testCount<<endl;
	outfile.close();
}

// Temporarily useless
extern "C" STRATEGY_API void SetForm(Environment *Env) {}

// Debug version interface
/*extern "C" STRATEGY_API void StrategyStepDebug(Environment *Env, DataDebug *Data) {
	StrategyStep(Env);
	StrategyBasis *strategy_pointer = reinterpret_cast<StrategyBasis *>(Env->pointer);
	*Data = strategy_pointer->get_debugdata();
}
*/
