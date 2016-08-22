#ifndef _XL_GLOBAL_H 
#define _XL_GLOBAL_H 
 
#define  ENABLE_LOG     //�����������log�ļ���ע�͵����м��� 
//#define  OFFLINE_CLIENT //���߿ͻ��� 
 
typedef unsigned int uint; 
 
// --------------Game-------------------------- 
const int    CROBOTNUM    = 5;       // ÿ���ӵĻ������� 
const int    CMATCHTIME   = 3000;    // �������� 
const int    CDEATHTIME   = 1000;    // ��ʱ���������� 
const int    CJSTIME      = 5000;    // ������������ 
// --------------------------------------------- 
 
// --------------Robot-------------------------- 
const double CMAXROBOTV        = 1.2;     // ��Ա����ٶ� 
const double CMAXROBOTACC      = 1.0;     // ��Ա�����ٶ� 
const double CMAXROBOTDECAY    = 0.4;     // ��Ա�ٶ�˥��ϵ�� 
const double CROBOTSIZE        = 0.3;     // �����˵İ뾶 
const double CKICKABLEMARGIN   = 0.7;     // �����˿���Χ 
const double CROBOTPTSIZE      = CROBOTSIZE + CKICKABLEMARGIN; 
const double CKICKPOWERRATE    = 0.027;	  // ������� 
const double CCATCHABLEMARGIN  = 1.5;     // ����Ա������Χ 
const double CCATCHMAXMOMENT   = 90;      // ����Ա��������н� 
const double CCATCHMINMOMENT   = -90;	  // ����Ա�������С�н� 
const double CCATCHPROBABILITY = 1.0;     // ����Ա����ɹ��� 
const int    CCATCHBANCYCLE    = 5;       // ����������ʱ�� 
const int    CMAXCATCHTIME     = 2;       // �������������� 
const double CMAXPOWER         = 100.0;   // ����������� 
const double CMINPOWER         = -100.0;  // ������С���� 
const double CMAXMOMENT        = 180.0;   // �������ת��Ƕ� 
const double CMINMOMENT        = -180.0;  // ������Сת��Ƕ� 
const double CINERTIAMOMENT    = 5.0;	  // ת����Բ��� 
const double CSTAMINAMAX       = 4000.0;  // ��Ա�������ֵ 
const double CSTAMINAINCMAX    = 45.0;    // ��Ա��������ָ�ֵ 
const double CDASHPOWERRATE    = 0.006;   // ��Ա����ϵ�� 
const double CEFFORTMIN        = 0.6;     // ��Ա��С����Ч��ֵ 
const double CEFFORTMAX        = 1.0;     // ��Ա�������Ч��ֵ 
const double CEFFORTDECTHR     = 0.3;     // ��Ա����Ч��ϵ�� 
const double CEFFORTDEC        = 0.005;   // ��Ա����Ч��ϵ�� 
const double CEFFORTINCTHR     = 0.6;     // ��Ա����Ч��ϵ�� 
const double CEFFORTINC        = 0.01;    // ��Ա����Ч��ϵ�� 
const double CRECOVERDECTHR    = 0.3;     // ��Ա�����ָ�ϵ������ 
const double CRECOVERDEC       = 0.002;   // ��Ա�����ָ�ϵ������������������ 
const double CRECOVERMAX       = 1.0;	  // ��Ա�����ָ�ϵ�� 
const double CRECOVERMIN       = 0.5;     // ��Ա�����ָ�ϵ�� 
const double CROBOTRAND        = 0.1;     // ��Ա�˶����ϵ�� 
const double CROBOTSEERANDPOS  = 5.0;     // ��Ա��֪�������������2�� 
const double CROBOTSEERANDVEL  = 0.5;     // ��Ա��֪�ٶ����������2�� 
// --------------------------------------------- 
 
// --------------Field-------------------------- 
const double CDOORWIDTH   = 4.0;        // ����һ����4.0��ʵ�ʳ�����2 * 4.0 
const double CPNZWIDTH    = 20.0;       // ������Ŀ�� 
const double CHALFPNZWIDTH= 10.0;       // ������İ��� 
const double CPNZLEN      = 10.25;      // ������ĳ��� 
const double CSPNZWIDTH   = 12.24;      // С�����Ŀ�� 
const double CHALFSPNZWIDTH = 6.12;     // С�����İ��� 
const double CSPNZLEN     = 5.2;        // С�����ĳ��� 
const double CFLDWIDTH    = 34.0;       // ���ؿ�� 
const double CHALFFLDWIDTH= 17.0;       // һ�볡�ؿ�� 
const double CFLDLEN      = 52.0;       // ���س��� 
const double CHALFFLDLEN  = 26.0;       // һ�볡�س��� 
const double CDOORY1	  = CHALFFLDWIDTH - CDOORWIDTH; // ������ 
const double CDOORY2	  = CHALFFLDWIDTH + CDOORWIDTH; // ������ 
// ---------------------------------------------- 
 
// --------------Ball----------------------------- 
const double CMAXBALLV    = 2.7;     // ������ٶ� 
const double CMAXBALLACC  = 2.7;     // �������ٶ� 
const double CBALLDECAY   = 0.94;    // ����˥��ϵ�� 
const double CBALLSIZE    = 0.085;   // ��İ뾶 
const double CBALLRAND    = 0.05;    // ����˶�����ϵ�� 
// ----------------------------------------------- 
 
const double CKICKABLEDIST  = CKICKABLEMARGIN + CROBOTSIZE + CBALLSIZE; 
const double CCATCHABLEDIST = CCATCHABLEMARGIN + CROBOTSIZE + CBALLSIZE; 
 
 
//������� 
 enum TeamSide 
 { 
	 TS_LEFT  = 1, 
	 TS_RIGHT = 2  
 }; 
 
 
// �������� 
enum CommandTypeT 
{ 
	Com_Stay = 0,  
	Com_Turn, //ת�� 
	Com_Kick, //���� 
	Com_Dash,  
	Com_Catch //���� 
}; 
 
 
/* 
��CommandType�ֱ�Ϊ�� 
	1) Stay : Server ���� Param1,Param2  
	2) Turn : Param1Ϊת��Ƕ�(��λ:��)��Server ����Param2  
	3) Kick : Param1Ϊ����Ƕ�(��λ:��)��Param2 Ϊ�������� 
	4) Dash : Param1Ϊdash power,Server����Param2  
	5) Catch: Server ���� Param1,Param2  
 */ 
struct TCommand 
{ 
    CommandTypeT Type;    //�������ࣺStay,Turn,Kick,Dash,Catch 
    double       Param1;  //�������1 
    double       Param2;  //�������2 
}; 
 
 
//��ά�ĵ� 
typedef struct 
{ 
   double x; 
   double y; 
} Vector;  
 
//�ҷ���Ա��Ϣ 
typedef struct  
{ 
	Vector pos; //λ�� 
	Vector vel; //�ٶ� 
	double dir; //���� 
	double sta; //���� 
	double eff; //����ʹ��Ч�� 
	double rec; //�����ָ�ֵ 
	bool   bComError; //���������Ƿ���� 
	bool   bCarsh; //�Ƿ�����ײ 
	bool   bCatch; //�Ƿ������� 
} RobotState; 
 
//�����Ϣ 
typedef struct  
{ 
	Vector pos; //λ�� 
	Vector vel; //�ٶ� 
	bool   bCarsh; //�Ƿ���ײ 
} BallState; 
 
//������Ϣ 
typedef struct 
{ 
	Vector pos; //λ�� 
	Vector vel; //�ٶ� 
	double dir; //���� 
} OpsState; 
 
typedef struct 
{ 
    int iTeam1Score; //1�Է��� 
    int iTeam2Score; //2�ӷ��� 
    int iTimeTipCnt; //�������Ժ��Դ���Ϣ 
    int iTimeNow; //��ǰ���� 
    int iTimeFromGoal; //��ǰ���ں����һ�ν���ļ�� 
    int iHMPETB; //�����Ժ��Դ���Ϣ 
} MatchState; // 24 Bytes 
 
const unsigned int SIZE_ROBOSTATES = sizeof(RobotState)*CROBOTNUM; 
 
#endif  
     
 