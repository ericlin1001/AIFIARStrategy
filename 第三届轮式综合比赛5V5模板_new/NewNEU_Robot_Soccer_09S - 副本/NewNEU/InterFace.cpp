    #include <windows.h>   
    #include "eisoo.h"   
    #include "InterFace.h"   
       
    //   
    // ȫ�ֶ���   
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
        //  // ����׹��ʱ�Ĳ���   
        //  //   
        //  case PLACE_KICK: {   
        //      g_decisionSystem.strategy (env);   
        //  }   
        //  break;     
        //     
        //  //   
        //  // ��������ʱ�Ĳ���   
        //  //   
        //  case PENALTY_KICK: {   
       
        //  }   
        //  break;   
       
        //  //   
        //  // ����������ʱ�Ĳ���   
        //  //   
        //  case FREE_KICK: {   
       
        //  }   
        //  break;   
       
        //  //   
        //  // ��������ʱ�Ĳ���   
        //  //   
        //  case GOAL_KICK: {   
       
        //  }              
        //  break;   
        //}   
    }  


