    //////////////////////////////////////////////////////////////////////////   
    // DUT 5vs5 RoboCup Team DLL FrameWork    
    // Specified Edition for M$ Visual C++   
    //   
    // Please don't modify any definition given by the DUT RoboCup Competition Committee.   
    // This is not compatible with the server of earlier version.   
    //   
    // Technology support E-Mail: guangbincui@gmail.com��brton.rei@gmail.com   
    //////////////////////////////////////////////////////////////////////////   
       
    // ע�⣺����������ݿ��Ը����Լ�����Ҫ�ı�   
    // ��������DLL��Ҫʹ��OOP����������ȫ������д��ʼ���ʹ洢����   
    // ��������ر������и����ӿڣ�����������������   
       
    // �������VC++�г������±�������    
    // unexpected end of file while looking for precompiled header directive   
    // ����Project->Settings->C/C++->Category->Precompiled Headersҳ   
    // ѡ��Not using precompiled headers   
       
    #include <windows.h>   
    #include "xianglong.h"   
       
       
       
    // ������������������ʹ��Բ����"("��")"   
       
    // ��ӵ����ƣ����𳬹�10������(20��ASCII�ַ�)��������ಿ�ֻᱻ����   
    #define  CTEAMNAME           "���";     
    // ���ߵ����������𳬹�7������(14��ASCII�ַ�)��������ಿ�ֻᱻ����   
    #define  CTEAMAUTHORS        "��������";     
       
       
    BOOL APIENTRY DllMain( HANDLE hModule,    
                           DWORD  ul_reason_for_call,    
                           LPVOID lpReserved   
                         )   
    {   
        return TRUE;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // ��ʼ�������Ϣ   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall initdll(int teamSide)   
    {   
        InitTeamSide(teamSide);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // ���±�����Ϣ   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall tellmatchstate(MatchState ams,   
                                                         RobotState arsOur[5],    
                                                         OpsState arsOpp[5],    
                                                         BallState abs)   
    {   
        UpdateMessage(ams,arsOur,arsOpp,abs);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // ȡ����ӵ�����   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) char* _stdcall teamname()   
    {   
        return CTEAMNAME;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // ȡ����ӵ�������   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) char* _stdcall teamauthor()   
    {   
        return CTEAMAUTHORS;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // �趨��Ա�Ķ���   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall setaction(TCommand * pMyCMD)   
    {   
        MakeDecision(pMyCMD);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // �˳���̬���ӿ⣬������Դ   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall exitdll()   
    {   
       ExitMatch();   
    }   


