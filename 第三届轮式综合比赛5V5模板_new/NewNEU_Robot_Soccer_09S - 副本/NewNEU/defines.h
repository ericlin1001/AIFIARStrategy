#ifndef NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_
#define NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_

// Frequency
#define FREQUENCY				0.2f

/*
// whoseBall
#define ANYONES_BALL			0
#define BLUE_BALL				1//mine
#define YELLOW_BALL				2//opp

// DEGameGround
#define	LEFT_AREA				0
#define	RIGHT_AREA 				1

// DEStartState
#define	DEFENSE					1
#define	ATTACK					0

// DEStartMode
#define NORMAL					0
#define FREE_BALL				1
#define PENALTY_KICK			2
#define FREE_KICK				3
#define GOAL_KICK				4
#define UNDER_WAY				5

*/
// SimuroSot5 

#define PITCH_LENGTH 			220
#define PITCH_WIDTH 	 		180
#define PENALTY_AREA_LENGTH		35
#define PENALTY_AREA_WIDTH		80
#define GOAL_AREA_LENGTH		15
#define GOAL_AREA_WIDTH			50
#define GOAL_WIDTH				40
#define GOAL_DEPTH				15

#define ROBOT_LENGTH			4
#define BALL_SIZE				2.0

#define MAX_SPEED				100//rad/s

#endif  // NEWNEU_ROBOT_SOCCER_09S_DEFINES_H_

/*
1)	决策坐标原点在场地围墙内左下角，俯视图中X轴正向水平向右，Y轴正向水平向上；
2)	长度单位为厘米，比例为1：1，取值范围取决于场地的大小；
3)	角度坐标的零方向为X轴正向，逆时针为正；
4)	角度单位为度数，比例为1：1，取值范围为(-180,180]。
*/
/*
0号足球机器人的左轮轮速，取值范围为[-100,100]，单位是rad/s；
e)	public double home0_velocityRight：0号足球机器人的右轮轮速，取值范围为[-100,100]，单位是rad/s；
*/
/*6)	球
直径42.7mm，重46g。
*/
/*2)	StrategyStep函数
C原型：extern "C" __declspec(dllexport) void StrategyStep ( Environment *env )
功能：实现控制决策，根据传入的状态数据决策出左右轮速，设置状态数据中的相应变量，实现足球机器人的控制。
调用周期：30ms
*/
/*10)	足球机器人正常运行的速度范围是[－100，100]，单位是rad/s，
车轮的半径是2cm。超过此范围可能会导致足球机器人翻车，
当决策给出的轮速超过100时，仿真平台只按100算。*/
/*机器人
     机器人为7.5cm×7.5cm×4.5cm 的小车机器人。
*/
/*(a）场地尺寸
赛场为黑色长方形场地，其尺寸是220cm×180cm ，带有5cm 高，2.5cm 厚的白色围墙。在场地的四角固定四个7cm×7cm 的等腰三角形以避免球进入角落。
（b）场地标记(附录2)
中圈半径是25cm 。作为门区的一部分的圆弧沿球门线长25cm ，垂直于球门线5cm。主要直线/圆弧（中线、门区边界线和中圈）均为白色，3mm 宽。争球时机器人的站位（圆）标记为灰色。
（c）球门
球门宽40cm，没有横梁和网。
（d）门线与门区
门线是恰好位于球门前长40cm 的直线。门区（附录2 中的区域A） 包括位于球门前尺寸为50cm×15cm 的长方形区域。
（e）罚球区
罚球区（附录2 中的区域B）球门前尺寸为80cm×35cm 的长方形区域，弧形区域平行于球门线长度为25cm ，垂直于球门线高度为5cm。
（f）球
用桔黄色的高尔夫球作比赛用球，直径42.7mm，重46g。
（g）机器人
     机器人为7.5cm×7.5cm×4.5cm 的小车机器人。
*/