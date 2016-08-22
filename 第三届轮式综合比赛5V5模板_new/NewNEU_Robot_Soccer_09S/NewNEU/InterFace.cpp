    #include <windows.h>   
    #include "eisoo.h"   
    #include "InterFace.h"   
       
    //   
    // 全局对象   
    //   
    DecisionSystem g_decisionSystem;   
       
    BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )   
    {       
        return TRUE;   
    }   
       
    extern "C" STRATEGY_API void Create ( Environment *env )   
    {   
    }   
       
    extern "C" STRATEGY_API void Destroy ( Environment *env )   
    {   
    }   
       
    extern "C" STRATEGY_API void Strategy ( Environment *env )   
    {   
        analyseFieldInfo (env->home[0].pos.x);   
        g_decisionSystem.strategy (env);   
       
        //switch (env->gameState)   
        //{   
        //  case 0: {   
        //      g_decisionSystem.strategy (env);               
        //  }   
        //  break;   
        //     
        //  case FREE_BALL: {   
        //      g_decisionSystem.strategy (env);   
        //  }   
        //  break;   
       
        //  //   
        //  // 发生坠球时的策略   
        //  //   
        //  case PLACE_KICK: {   
        //      g_decisionSystem.strategy (env);   
        //  }   
        //  break;     
        //     
        //  //   
        //  // 发生罚球时的策略   
        //  //   
        //  case PENALTY_KICK: {   
       
        //  }   
        //  break;   
       
        //  //   
        //  // 发生任意球时的策略   
        //  //   
        //  case FREE_KICK: {   
       
        //  }   
        //  break;   
       
        //  //   
        //  // 发生点球时的策略   
        //  //   
        //  case GOAL_KICK: {   
       
        //  }              
        //  break;   
        //}   
    }  


