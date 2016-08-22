#ifndef NEWNEUROBOTSOCCER09S_NEWNEU_H_
#define NEWNEUROBOTSOCCER09S_NEWNEU_H_

#define STRATEGY_API __declspec(dllexport)

#include "interface.h"

/* MUST BE IMPLEMENTED */
extern "C" STRATEGY_API void StrategyInit(Environment * Env);
extern "C" STRATEGY_API void StrategyStep(Environment * Env);
extern "C" STRATEGY_API void StrategyDrop(Environment * Env);
extern "C" STRATEGY_API void Author(char * team);
extern "C" STRATEGY_API void SetForm(Environment * Env);
//extern "C" STRATEGY_API void StrategyStepDebug(Environment * Env, DataDebug * Data);

#endif  // NEWNEUROBOTSOCCER09S_NEWNEU_H_
