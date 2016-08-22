#ifndef _XIANGLONG_H 
#define _XIANGLONG_H 
#include "xl_coach.h" 
 
__declspec( dllexport ) void _stdcall setaction(TCommand *pMyCMD); 
extern "C" __declspec( dllexport ) char* _stdcall teamauthor(); 
extern "C" __declspec( dllexport ) char* _stdcall teamname(); 
__declspec( dllexport ) void _stdcall tellmatchstate(MatchState ams, RobotState atmAs[5], RobotState atmBs[5], BallState abs); 
__declspec( dllexport ) void _stdcall initdll(int initTeamNo); 
__declspec( dllexport ) void _stdcall exitdll(); 
 
#endif 
 
 
 
 