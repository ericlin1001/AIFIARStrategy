// Strategy.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Strategy.h"

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


//Global Environment variable
static Environment gloabe;
//
#include<fstream>
#include<iostream>
using namespace std;

extern "C" STRATEGY_API void StrategyInit(Environment* Env)
{
	ofstream outfile;
	outfile.open("thisisarealyspecial.txt");
	if(!outfile.fail()){
		outfile<<"adfadf"<<endl;
	}else{
		cout<<"open fail"<<endl;
	}
	//Please allocate your own resource here
	//e.g.	
	//Env->pointer=(long)new CDecisionMakingx();
}

extern "C" STRATEGY_API void StrategyStep(Environment* Env)
{
	//Please GET the information of robots first,
	//After strategy making,SET the speed of wheels.
	Env->home0_velocityLeft=70;
	Env->home0_velocityRight=90;
	//
	Env->home1_velocityLeft=70;
	Env->home1_velocityRight=90;
	Env->home2_velocityLeft=3;
	Env->home2_velocityRight=2;
	//Env->home3_velocityLeft=3;
	//Env->home4_velocityRight=2;

}
extern "C" STRATEGY_API void StrategyDrop(	Environment* Env)
{
	Env->home0_velocityLeft=70;
	Env->home0_velocityRight=90;
	//
	Env->home1_velocityLeft=70;
	Env->home1_velocityRight=90;
	Env->home2_velocityLeft=3;
	Env->home2_velocityRight=2;
	Env->home3_velocityLeft=3;
	Env->home4_velocityRight=2;
	//Free the resource you allocated

	//e.g.
	//if(NULL!=Env->pointer)
	//{
	//	delete (CDecisionMakingx*)(Env->pointer);
	//}
	//Env->pointer=NULL;
}


extern "C" STRATEGY_API void SetForm(Environment* Env)
{
	//Please GET the information of robots first,
	//Then,SET the location of robots(sometimes,including the ball).
}
extern "C" STRATEGY_API void Author(char* team)
{
	strcpy(team,"test2");
	//Please give you strategy a nice name
	//e.g.
	//strcpy(team,"Cool!");
}
/*1)	StrategyInit函数
C原型：extern "C" __declspec(dllexport) void StrategyInit ( Environment *env )
功能：分配决策DLL文件中的资源，并将其地址赋值给pointer。
调用周期：仅在加载DLL时调用一次。
2)	StrategyStep函数
C原型：extern "C" __declspec(dllexport) void StrategyStep ( Environment *env )
功能：实现控制决策，根据传入的状态数据决策出左右轮速，设置状态数据中的相应变量，实现足球机器人的控制。
调用周期：30ms
3)	StrategyDrop函数
C原型：extern "C" __declspec(dllexport) void StrategyDrop ( Environment *env )
功能：释放资源，并将资源的指针pointer置为NULL。
调用周期：仅在卸载DLL时调用一次。
4)	Author函数
C原型：extern "C" __declspec(dllexport) void Author ( char *env )
功能：提取表征作者身份的唯一标识，将被显示在控制面板上。
调用周期：仅在加载DLL时调用一次。
*/
/*8)	kickOffStyle信号量仅在裁判更改开球方式后仅被更新－次，之后将由决策文件维护，直到新的开球方式被裁判选择。
9)	请注意接口数据结构变量的取值范围和单位。 
10)	足球机器人正常运行的速度范围是[－100，100]，单位是rad/s，车轮的半径是2cm。超过此范围可能会导致足球机器人翻车，当决策给出的轮速超过100时，仿真平台只按100算。
*/