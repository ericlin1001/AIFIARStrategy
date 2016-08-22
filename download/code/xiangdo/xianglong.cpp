    //////////////////////////////////////////////////////////////////////////   
    // DUT 5vs5 RoboCup Team DLL FrameWork    
    // Specified Edition for M$ Visual C++   
    //   
    // Please don't modify any definition given by the DUT RoboCup Competition Committee.   
    // This is not compatible with the server of earlier version.   
    //   
    // Technology support E-Mail: guangbincui@gmail.com，brton.rei@gmail.com   
    //////////////////////////////////////////////////////////////////////////   
       
    // 注意：函数体的内容可以根据自己的需要改变   
    // 例如你在DLL中要使用OOP技术，你完全可以重写初始化和存储部分   
    // 但是请务必保持所有给定接口（函数）的声明部分   
       
    // 另：如果在VC++中出现如下编译问题    
    // unexpected end of file while looking for precompiled header directive   
    // 请在Project->Settings->C/C++->Category->Precompiled Headers页   
    // 选择Not using precompiled headers   
       
    #include <windows.h>   
    #include "xianglong.h"   
       
       
       
    // 以下两项名称中请勿使用圆括号"("和")"   
       
    // 球队的名称，请勿超过10个汉字(20个ASCII字符)，否则多余部分会被忽略   
    #define  CTEAMNAME           "零空";     
    // 作者的姓名，请勿超过7个汉字(14个ASCII字符)，否则多余部分会被忽略   
    #define  CTEAMAUTHORS        "作者名字";     
       
       
    BOOL APIENTRY DllMain( HANDLE hModule,    
                           DWORD  ul_reason_for_call,    
                           LPVOID lpReserved   
                         )   
    {   
        return TRUE;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 初始化球队信息   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall initdll(int teamSide)   
    {   
        InitTeamSide(teamSide);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 更新比赛信息   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall tellmatchstate(MatchState ams,   
                                                         RobotState arsOur[5],    
                                                         OpsState arsOpp[5],    
                                                         BallState abs)   
    {   
        UpdateMessage(ams,arsOur,arsOpp,abs);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 取得球队的名称   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) char* _stdcall teamname()   
    {   
        return CTEAMNAME;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 取得球队的作者名   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) char* _stdcall teamauthor()   
    {   
        return CTEAMAUTHORS;   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 设定球员的动作   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall setaction(TCommand * pMyCMD)   
    {   
        MakeDecision(pMyCMD);   
    }   
       
    //////////////////////////////////////////////////////////////////////////   
    // 退出动态链接库，回收资源   
    //////////////////////////////////////////////////////////////////////////   
    __declspec( dllexport ) void _stdcall exitdll()   
    {   
       ExitMatch();   
    }   


