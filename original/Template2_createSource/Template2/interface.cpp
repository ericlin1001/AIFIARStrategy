#include "stdafx.h"
#include "interface.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
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
extern "C" STRATEGY_API void StrategyInit(Environment* Env){

}
extern "C" STRATEGY_API void StrategyStep(Environment* Env){

}
extern "C" STRATEGY_API void StrategyDrop(Environment* Env){

}
extern "C" STRATEGY_API void Author(char* team){
	strcpy(team,"Template2");

}
extern "C" STRATEGY_API void SetForm(Environment* Env){

}