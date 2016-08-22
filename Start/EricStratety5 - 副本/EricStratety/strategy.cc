#include "stdafx.h"
#include "strategy.h"
#include "strategy-inl.h"

#include <iostream>

// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
// Constructor.
StrategyBasis::StrategyBasis(const char *logFile,const char *debugDataFile,const int t) {
  // Initialize the data file path
  filedata_.SetFile(debugDataFile);
  // Initialize log type
  int type = t;
  if (!type) {
    logger_.OpenConsole();
  }
  else {
    logger_.OpenFile(
        logFile);
  }
}

// Entrance of the strategy.
void 
StrategyBasis::Start(const Object objects[]) {
  // Copy parameters information to local members
  for (int i = 0; i < ROBOT_NUMBER; ++i) {
    robots_[i].Update(objects[i].get_position(), 
                      objects[i].get_vector(),
                      objects[i].get_theta());
    opponents_[i].Update(objects[ROBOT_NUMBER + i].get_position(),
                         objects[ROBOT_NUMBER + i].get_vector(),
                         objects[ROBOT_NUMBER + i].get_theta());
  }
  ball_.Update(objects[ROBOT_NUMBER * 2].get_position(),
               objects[ROBOT_NUMBER * 2].get_vector(),
               objects[ROBOT_NUMBER * 2].get_theta());

  // Process strategy
  PreProcess();
  DecisionMaking();
  PostProcess();
}

// Pre-process.
void 
StrategyBasis::PreProcess() {
  // For better convenience, shift coordinate to 
  // keep home field always on the left side.
	if (BallField::RIGHT == gs_.myField) {
		VecPosition fieldPos=VecPosition(FIELD_INFO::LENGTH,FIELD_INFO::WIDTH);
    for (int i = 0; i < ROBOT_NUMBER; ++i) {
		robots_[i].set_position(fieldPos-robots_[i].get_position());
      robots_[i].set_theta(
          VecPosition::NormalizeAngle(robots_[i].get_theta() + PI));
      opponents_[i].set_position(fieldPos - opponents_[i].get_position());
      opponents_[i].set_theta(VecPosition::NormalizeAngle(opponents_[i].get_theta() + PI));
    }
    ball_.set_position(fieldPos-ball_.get_position());
  }
  // Respond to match state
	
}

// Strategy process.
void 
StrategyBasis::DecisionMaking() {
  // Reset all the robot speeds
  for (int i = 0; i < ROBOT_NUMBER; ++i) {
    robots_[i].set_left_velocity(0.0);
    robots_[i].set_right_velocity(0.0);
  }
  // TODO: Add strategy detail here.
}

// Post-process.
void 
StrategyBasis::PostProcess() {
  // Temporarily nothings' done here
	if (gs_.matchState!=MatchState::MS_UNDER_WAY) {
    // TODO: Add some mark to respond to different situation.
		gs_.matchState=MatchState::MS_UNDER_WAY;
	}
}
// ---- ---- ---- ---- Class StrategyBasis ---- ---- ---- ----
