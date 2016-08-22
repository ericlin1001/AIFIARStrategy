#ifndef _XL_COACH_H_ 
#define _XL_COACH_H_ 
 
#include "xl_global.h" 
 
void InitTeamSide(int teamSide); 
void UpdateMessage( MatchState ams, RobotState arsTeam[5],OpsState arsOpp[5], BallState abs); 
void MakeDecision(TCommand * pMyCMD); 
void ExitMatch(); 
 
#endif 