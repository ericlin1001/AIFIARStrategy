    #include "xl_coach.h"   
    #include "xl_logger.h"   
    #include <stdlib.h>   
    #include <stdio.h>   
    #include <memory.h>   
       
    MatchState      matchState; //������Ϣ   
    RobotState      ourTeamState[5]; //�ҷ���Ա��Ϣ   
    OpsState        opsTeamState[5]; //������Ϣ   
    BallState       ballState;   //����Ϣ   
    TeamSide        ourTeamSide; //���Ҷ�   
       
    /*  
    // ��������  
    enum CommandTypeT  
    {  
        Com_Stay = 0,   
        Com_Turn, //ת��  
        Com_Kick, //����  
        Com_Dash,   
        Com_Catch //����  
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
        //ҪʹĳƵ����Ч���������RegisterChannel   
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
       
    //��ǰ�˺���������������õģ���Ա����ܶ���������ʱ�ͳ���ǰ����   
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
        //�ر�Log�ļ�   
        CloseLogger();   
    #endif   
    }   