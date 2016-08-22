#ifndef _XL_GLOBAL_H 
#define _XL_GLOBAL_H 
 
#define  ENABLE_LOG     //如果不想生成log文件，注释掉此行即可 
//#define  OFFLINE_CLIENT //离线客户端 
 
typedef unsigned int uint; 
 
// --------------Game-------------------------- 
const int    CROBOTNUM    = 5;       // 每个队的机器人数 
const int    CMATCHTIME   = 3000;    // 仿真周期 
const int    CDEATHTIME   = 1000;    // 加时赛仿真周期 
const int    CJSTIME      = 5000;    // 决赛仿真周期 
// --------------------------------------------- 
 
// --------------Robot-------------------------- 
const double CMAXROBOTV        = 1.2;     // 球员最大速度 
const double CMAXROBOTACC      = 1.0;     // 球员最大加速度 
const double CMAXROBOTDECAY    = 0.4;     // 球员速度衰减系数 
const double CROBOTSIZE        = 0.3;     // 机器人的半径 
const double CKICKABLEMARGIN   = 0.7;     // 机器人控球范围 
const double CROBOTPTSIZE      = CROBOTSIZE + CKICKABLEMARGIN; 
const double CKICKPOWERRATE    = 0.027;	  // 踢球参数 
const double CCATCHABLEMARGIN  = 1.5;     // 守门员的扑球范围 
const double CCATCHMAXMOMENT   = 90;      // 守门员扑球的最大夹角 
const double CCATCHMINMOMENT   = -90;	  // 守门员扑球的最小夹角 
const double CCATCHPROBABILITY = 1.0;     // 守门员扑球成功率 
const int    CCATCHBANCYCLE    = 5;       // 两次扑球间隔时间 
const int    CMAXCATCHTIME     = 2;       // 最多连续扑球次数 
const double CMAXPOWER         = 100.0;   // 命令最大力量 
const double CMINPOWER         = -100.0;  // 命令最小力量 
const double CMAXMOMENT        = 180.0;   // 命令最大转身角度 
const double CMINMOMENT        = -180.0;  // 命令最小转身角度 
const double CINERTIAMOMENT    = 5.0;	  // 转身惯性参数 
const double CSTAMINAMAX       = 4000.0;  // 球员最大体力值 
const double CSTAMINAINCMAX    = 45.0;    // 球员最大体力恢复值 
const double CDASHPOWERRATE    = 0.006;   // 球员加速系数 
const double CEFFORTMIN        = 0.6;     // 球员最小体力效用值 
const double CEFFORTMAX        = 1.0;     // 球员最大体力效用值 
const double CEFFORTDECTHR     = 0.3;     // 球员体力效用系数 
const double CEFFORTDEC        = 0.005;   // 球员体力效用系数 
const double CEFFORTINCTHR     = 0.6;     // 球员体力效用系数 
const double CEFFORTINC        = 0.01;    // 球员体力效用系数 
const double CRECOVERDECTHR    = 0.3;     // 球员体力恢复系数？？ 
const double CRECOVERDEC       = 0.002;   // 球员体力恢复系数？？？？？？？？ 
const double CRECOVERMAX       = 1.0;	  // 球员体力恢复系数 
const double CRECOVERMIN       = 0.5;     // 球员体力恢复系数 
const double CROBOTRAND        = 0.1;     // 球员运动误差系数 
const double CROBOTSEERANDPOS  = 5.0;     // 球员感知坐标最大噪声的2倍 
const double CROBOTSEERANDVEL  = 0.5;     // 球员感知速度最大噪声的2倍 
// --------------------------------------------- 
 
// --------------Field-------------------------- 
const double CDOORWIDTH   = 4.0;        // 球门一侧是4.0，实际长度是2 * 4.0 
const double CPNZWIDTH    = 20.0;       // 大禁区的宽度 
const double CHALFPNZWIDTH= 10.0;       // 大禁区的半宽度 
const double CPNZLEN      = 10.25;      // 大禁区的长度 
const double CSPNZWIDTH   = 12.24;      // 小禁区的宽度 
const double CHALFSPNZWIDTH = 6.12;     // 小禁区的半宽度 
const double CSPNZLEN     = 5.2;        // 小禁区的长度 
const double CFLDWIDTH    = 34.0;       // 场地宽度 
const double CHALFFLDWIDTH= 17.0;       // 一半场地宽度 
const double CFLDLEN      = 52.0;       // 场地长度 
const double CHALFFLDLEN  = 26.0;       // 一半场地长度 
const double CDOORY1	  = CHALFFLDWIDTH - CDOORWIDTH; // 上门柱 
const double CDOORY2	  = CHALFFLDWIDTH + CDOORWIDTH; // 下门柱 
// ---------------------------------------------- 
 
// --------------Ball----------------------------- 
const double CMAXBALLV    = 2.7;     // 球最大速度 
const double CMAXBALLACC  = 2.7;     // 球最大加速度 
const double CBALLDECAY   = 0.94;    // 球速衰减系数 
const double CBALLSIZE    = 0.085;   // 球的半径 
const double CBALLRAND    = 0.05;    // 球的运动噪声系数 
// ----------------------------------------------- 
 
const double CKICKABLEDIST  = CKICKABLEMARGIN + CROBOTSIZE + CBALLSIZE; 
const double CCATCHABLEDIST = CCATCHABLEMARGIN + CROBOTSIZE + CBALLSIZE; 
 
 
//左右球队 
 enum TeamSide 
 { 
	 TS_LEFT  = 1, 
	 TS_RIGHT = 2  
 }; 
 
 
// 命令种类 
enum CommandTypeT 
{ 
	Com_Stay = 0,  
	Com_Turn, //转身 
	Com_Kick, //踢球 
	Com_Dash,  
	Com_Catch //扑球 
}; 
 
 
/* 
当CommandType分别为： 
	1) Stay : Server 忽略 Param1,Param2  
	2) Turn : Param1为转身角度(单位:度)，Server 忽略Param2  
	3) Kick : Param1为踢球角度(单位:度)，Param2 为踢球力量 
	4) Dash : Param1为dash power,Server忽略Param2  
	5) Catch: Server 忽略 Param1,Param2  
 */ 
struct TCommand 
{ 
    CommandTypeT Type;    //命令种类：Stay,Turn,Kick,Dash,Catch 
    double       Param1;  //命令参数1 
    double       Param2;  //命令参数2 
}; 
 
 
//二维的点 
typedef struct 
{ 
   double x; 
   double y; 
} Vector;  
 
//我方球员信息 
typedef struct  
{ 
	Vector pos; //位置 
	Vector vel; //速度 
	double dir; //方向 
	double sta; //体力 
	double eff; //体力使用效率 
	double rec; //体力恢复值 
	bool   bComError; //发送命令是否错误 
	bool   bCarsh; //是否发生碰撞 
	bool   bCatch; //是否在扑球 
} RobotState; 
 
//球的信息 
typedef struct  
{ 
	Vector pos; //位置 
	Vector vel; //速度 
	bool   bCarsh; //是否碰撞 
} BallState; 
 
//对手信息 
typedef struct 
{ 
	Vector pos; //位置 
	Vector vel; //速度 
	double dir; //方向 
} OpsState; 
 
typedef struct 
{ 
    int iTeam1Score; //1对分数 
    int iTeam2Score; //2队分数 
    int iTimeTipCnt; //？，可以忽略此信息 
    int iTimeNow; //当前周期 
    int iTimeFromGoal; //当前周期和最近一次进球的间隔 
    int iHMPETB; //？可以忽略此信息 
} MatchState; // 24 Bytes 
 
const unsigned int SIZE_ROBOSTATES = sizeof(RobotState)*CROBOTNUM; 
 
#endif  
     
 