    #include "xl_coach.h"   
    #include "xl_logger.h"   
    #include <stdlib.h>   
    #include <stdio.h>   
    #include <memory.h>   
       
    MatchState      matchState; //比赛信息   
    RobotState      ourTeamState[5]; //我方球员信息   
    OpsState        opsTeamState[5]; //对手信息   
    BallState       ballState;   //球信息   
    TeamSide        ourTeamSide; //左右队   
       
    /*  
    // 命令种类  
    enum CommandTypeT  
    {  
        Com_Stay = 0,   
        Com_Turn, //转身  
        Com_Kick, //踢球  
        Com_Dash,   
        Com_Catch //扑球  
    };  
    */   
    const char* cmdName[]=   
    {      
        "Stay",   
        "Turn",   
        "Kick",   
        "Dash",   
        "Catch"   
    };   
       
       
    void InitTeamSide(int teamSide)   
    {   
    #ifdef ENABLE_LOG   
        OpenLogger("debug.log");   
        //要使某频道有效，必须调用RegisterChannel   
        RegisterChannel(CT_ERROR,"ERROR");   
        RegisterChannel(CT_TEST,"TEST");   
        RegisterChannel(CT_SENSE,"SENSE");   
        RegisterChannel(CT_CMD,"CMD");   
    #endif   
        if(teamSide ==TS_LEFT)    
        {   
            ourTeamSide = TS_LEFT;   
        }    
        else if(teamSide ==TS_RIGHT)    
        {   
            ourTeamSide = TS_RIGHT;   
        }   
        else   
        {   
            Log(CT_ERROR,"(ourTeamSide %d)",ourTeamSide);   
        }   
        Log(CT_TEST,"(ourTeamSide %d)",ourTeamSide);   
    }   
       
    void UpdateMessage( MatchState ams,   
                        RobotState arsOur[5],   
                        OpsState arsOpp[5],    
                        BallState abs)   
    {   
        memcpy(&matchState, &ams, sizeof(MatchState));   
        memcpy(ourTeamState, arsOur, sizeof(RobotState)*5);   
        memcpy(opsTeamState, arsOpp, sizeof(OpsState)*5);   
        memcpy(&ballState, &abs, sizeof(BallState));   
       
        SetLogCycle(matchState.iTimeNow);   
        for (int i = 0;i<5;i++)   
        {   
            Log(CT_SENSE,"(OurRobot (idx %d)(pos %.3f %.3f)(vel %.3f %.3f)(dir %.1f)(sta %.1f)",   
                i,ourTeamState[i].pos.x,ourTeamState[i].pos.y,   
                ourTeamState[i].vel.x,ourTeamState[i].vel.y,   
                ourTeamState[i].dir,ourTeamState[i].sta);   
            Log(CT_SENSE,"(OpsRobot (idx %d)(pos %.3f %.3f)(vel %.3f %.3f)",   
                i,opsTeamState[i].pos.x,opsTeamState[i].pos.y,   
                opsTeamState[i].vel.x,opsTeamState[i].vel.y);   
        }   
           
    }   
       
    //当前此函数代码是随便设置的，球员随机跑动，可踢球时就朝正前方踢   
    void MakeDecision(TCommand * pMyCMD)   
    {   
        for (int i = 0 ; i  5 ; i++ )   
        {      
            if(i>3)   
            {   
                pMyCMD[i].Type = Com_Turn;   
                pMyCMD[i].Param1 = 20;   
            }   
            else   
            {   
                pMyCMD[i].Type = Com_Dash;   
                pMyCMD[i].Param1   = CMAXPOWER * 0.5;   
            }   
       
            Log(CT_CMD,"(Robot %d) (%s  %.3f %.3f)",   
                i,cmdName[pMyCMD[i].Type],   
                pMyCMD[i].Param1,pMyCMD[i].Param2);   
        }   
    }   
       
    void  ExitMatch()   
    {   
    #ifdef ENABLE_LOG   
        //关闭Log文件   
        CloseLogger();   
    #endif   
    }   