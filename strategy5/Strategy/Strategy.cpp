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
/*1)	StrategyInit����
Cԭ�ͣ�extern "C" __declspec(dllexport) void StrategyInit ( Environment *env )
���ܣ��������DLL�ļ��е���Դ���������ַ��ֵ��pointer��
�������ڣ����ڼ���DLLʱ����һ�Ρ�
2)	StrategyStep����
Cԭ�ͣ�extern "C" __declspec(dllexport) void StrategyStep ( Environment *env )
���ܣ�ʵ�ֿ��ƾ��ߣ����ݴ����״̬���ݾ��߳��������٣�����״̬�����е���Ӧ������ʵ����������˵Ŀ��ơ�
�������ڣ�30ms
3)	StrategyDrop����
Cԭ�ͣ�extern "C" __declspec(dllexport) void StrategyDrop ( Environment *env )
���ܣ��ͷ���Դ��������Դ��ָ��pointer��ΪNULL��
�������ڣ�����ж��DLLʱ����һ�Ρ�
4)	Author����
Cԭ�ͣ�extern "C" __declspec(dllexport) void Author ( char *env )
���ܣ���ȡ����������ݵ�Ψһ��ʶ��������ʾ�ڿ�������ϡ�
�������ڣ����ڼ���DLLʱ����һ�Ρ�
*/
/*8)	kickOffStyle�ź������ڲ��и��Ŀ���ʽ��������£��Σ�֮���ɾ����ļ�ά����ֱ���µĿ���ʽ������ѡ��
9)	��ע��ӿ����ݽṹ������ȡֵ��Χ�͵�λ�� 
10)	����������������е��ٶȷ�Χ��[��100��100]����λ��rad/s�����ֵİ뾶��2cm�������˷�Χ���ܻᵼ����������˷����������߸��������ٳ���100ʱ������ƽֻ̨��100�㡣
*/