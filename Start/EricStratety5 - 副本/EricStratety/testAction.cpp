#include "stdafx.h"
#include "action.h"
/**************************************************************************************************** 
action.h 艾数机器人角色动作头文件 

Purpose: 
角色可以使用的动作 

author: 
yy_cn 

Created Time: 
2006-5-10 
****************************************************************************************************/ 

/** 
* robot 是否可以射门 
* robotX 机器人的 X 坐标 
* robotY 机器人的 Y 坐标 
* ballX 球的 X 坐标 
* ballY 球的 Y 坐标 
* 不需要将坐标转换 
* @return == true 可以射门 
* @return == false 不可以射门 
*/ 
bool canShoot (double robotX, double robotY, double ballX, double ballY){
	//Show("canShoot");
	if(robotX>ballX)return false;

	double targetX = OPP_GOAL_CENTER_X;   
    double targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
   
    //   
    // targetY 为跟据 机器人 与 球 之间角度求出 targetX 处 Y 值   
    //   
    if (targetY < GTOPY && targetY > GBOTY)   
        return true;   
   
    return false; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 动作系统，提供机器人角色的一系统动作支持 
// 
// 
// 基本动作，由基本动作来组合成复杂的动作 
// 

/** 
* 设置小车轮数 
*/ 
void actVelocity (Robot &robot, int vl, int vr){
	robot.set_left_velocity(vl);
	robot.set_right_velocity(vr);
} 

//	/** 
//	 * 机器人向某个方向运动 
//	 */ 
//	static void move (Robot &robot, BallDirection direction); 

/** 
* 原地旋传到指定角度 
* @param -180  angle  180 
*/ 
void actTurn (Robot &robot, double angle){
	robot.TurnToAngle(angle);
}  

/** 
* 将机器人移动到指定位置 
*/ 
#include "GeometryR.h"
inline void actToPosition (Robot &robot, double x, double y){
	robot.ToPositionPD(VecPosition(x,y));
}  

// 
// 由基本动作组成的复杂动作 
// 

/** 
* 射门 
* 如果角度或方位不正确则会使用移动动作移动到合适的位置 
*/ 
void actShoot (Robot &robot, const Environment &env)   
{   
    //   
    // 射门 - 踢球的情况相同   
    // 1. 机器人离球非常近，球的速度为中低速，则使用以下方法能够准确的射门   
    //    直接以 机器人的中心点 与 球的点心点 形成的一条直线向对方球门区域内移动   
    //    将移动的目标点设置为一个比较比较远的位置，此时机器人与球相撞产生的速度能让球快速移动   
    //    如果机器人当前的坐标不适合射门，则将机器人移动到一个合适的最近的位置   
    //   
    // 2. 机器人离球有一定的距离，球的速度为快速，则使用以下方法能够准确的射门   
    //    球的运动方向与机器人水平移动的方向能够产生一个交点   
    //    且产生交点的机器人移动的方向为敌方方向   
    //   
       
    //   
    // 暂时只考虑 1 的情况   
    //   
       
   
    //   
    // 射门，先实现简单方法，直接以机器人与球，球门中心的角度踢   
    //   
    // 有时间的话进行精确的计算，检查机器人，球，球门中心角度的直线上的敌人   
    // 射门角度以球所在的区域来击向敌方的死角   
    //   
    /*  
        +------------------+  
        |               6 7|  
        |-            1   -|  
        | |           2  | |  
        |-            3   -|  
        |               4 5|  
        +------------------+  
     */   
    double ballX = env.currentBall.pos.x;   
    double ballY = env.currentBall.pos.y;   
   
    double targetX, targetY;   
    if (canShoot (robot.pos.x, robot.pos.y, ballX, ballY) == false) {   
        //   
        // 角度不正确，移动机器人到合适的位置 - 面向对方球门方向，在球的边上   
        //   
 
        targetX = ballX - BALL_DIAMETER;
        //   
        // 移动的目标点为球门的边角   
        //   
        double shootX = OPP_GOAL_CENTER_X;   
        double shootY = 0;//OPP_GOAL_CENTER_Y;   
        if (robot.pos.y < ballY) {   
            //   
            // 机器人在球的下方   
            //   
            shootY = GTOPY - BALL_DIAMETER - BALL_DIAMETER;   
        }   
        else {   
            //   
            // 机器人在球的上方   
            //   
            shootY = GBOTY + BALL_DIAMETER - BALL_DIAMETER;   
        }   
   
        //   
        // 对方球门中心为第一个点，球为第二个点， targetX 为已知的 X 点，求出 targetY   
        //   
        targetY = getMappedTargetY (shootX, shootY, ballX, ballY, targetX);   
        if (targetX < FLEFTX || targetX > FRIGHTX || targetY < FBOT || targetY > FTOP) {   
            //   
            // 球靠近场地边框，直接撞球   
            //   
            actToPosition (robot, ballX, ballY);   
            //actBezier2Reach (robot, ballX, ballY, 2.5);   
            return;   
        }   
   
        //   
        // 移动到 targetX, targetY 点   
        //   
        actToPosition (robot, targetX, targetY);   
        //actBezier2Reach (robot, targetX, targetY, 2.5);   
        return;   
    }   
   
    //   
    // 角度正确，获得一个非常远的映射点的为目标点移动达到射门的目的   
    // 如果目标点很远，机器人离球越近则射门力度越大   
    //   
    targetX = FRIGHTX + FIELD_WIDTH / 2;
   
    targetY = getMappedTargetY (robot.pos.x, robot.pos.y, ballX, ballY, targetX);   
    actToPosition (robot, targetX, targetY);   
    //actBezier2Reach (robot, targetX, targetY, 2.5);   
} 
 
//   
// kickBall   
//   
/*  
      **********************************  
****** 以下参数均以我方在左半场为参考值 *******  
      **********************************  
  
          A     B          C      D  
        |--|---------|----------|---|  
        +---------------------------+  
        |            |              |  
       _|+++         |           +++|_  
      | |  +         |           +  | | ____ 中点 centerY  
      |_|  +         |           +  |_|  
        |+++         |           +++|  
        |            |              |  
        +---------------------------+  
        <-我方球场         敌方球场->  
  
        +---------------------------+  
        |            |              |  
       _|+++         | 1  2  3   +++|_ - GTOPY  
      | |  +         | 4  *  5   +  | | ____ 中点 centerY  
      |_|  +         | 6  7  8   +  |_|  
        |+++         |           +++|  - GBOTY  
        |            |              |  
        +---------------------------+  
        <-后                     前->  
  
        1,2,3,4,5,6,7,8 机器人位置  
        * 球的位置  
  
                          上  
        +---------------------------+  
        |            |              |  
       _|+++         |  1  2  3  +++|_   
   左 | |  +         |  4  *  5  +  | | 右  
      |_|  +         |  6  7  8  +  |_|  
        |+++         |           +++|  
        |            |              |  
        +---------------------------+  
                          下  
          
        机器人在球的 上方: 1, 2, 3  
                     左方: 4  
                     右方: 5  
                     下方: 6, 7, 8  
*/   
//   
// 踢球判断时将球场分为四个区域   
//   
enum KickArea   
{   
    KA_A,   // A   
    KA_B,   // B   
    KA_C,   // C   
    KA_D,   // D   
}; // end enum KickArea   
   
//   
// 踢球的方向   
//   
enum KickDirection   
{   
    KD_1,   
    KD_2,   
    KD_3,   
    KD_4,   
    KD_5,   
    KD_6,   
    KD_7,   
    KD_8,   
}; // end KickDirection   
   
//   
// 机器人在球的方向   
//   
enum RobotToBallDirection   
{   
    RBD_TOP,   
    RBD_LEFT,   
    RBD_RIGHT,   
    RBD_BOTTOM,   
}; // end enum RobotToBallDirection   
   
//   
// 分析踢球时所需的信息   
//   
void analyseKickInfo (Robot &robot,   
                      const Environment &env,   
                      KickArea &area,   
                      KickDirection &direction,   
                      RobotToBallDirection &rbd)   
{   
    double robotX = robot.pos.x;   
    double robotY = robot.pos.y;   
   
    double ballX = env.currentBall.pos.x;   
    double ballY = env.currentBall.pos.y;   
  
   
    //   
    // 先分析球在哪个区域   
    //   
    {   
        double aLeftX = FLEFTX,   
               bLeftX = FORBID_ZONE_X,   
               cLeftX = FIELD_CENTER_X,   
               dLeftX = OPP_FORBID_ZONE_X,   
               dRightX = FRIGHTX;   
   
        double tempY = 0;   
   
       
        if (aLeftX <= ballX && ballX <= bLeftX) 
            area = KA_A;   
        else if (bLeftX <= ballX && ballX <= cLeftX)   
            area = KA_B;   
        else if (cLeftX <= ballX && ballX <= dLeftX)   
            area = KA_C;   
        else if (dLeftX <= ballX && ballX <= dRightX)  
            area = KA_D;   
    }   
   
    //   
    // 分析机器人在球的哪个方向   0
    //   
    {   
        if (ballY == robotY) {   
            //   
            // 球的 X 坐标大于机器人的 X 坐标且我方在左半场则机器人在球的 左边   
            // 球的 X 坐标小于机器人的 X 坐标且我方在右半场则机器人在球的 左边   
            //   
            if (ballX > robotX )
                rbd = RBD_LEFT;   
            else   
                rbd = RBD_RIGHT;   
        }   
        else if (ballY <= robotY) {   
            //   
            // 机器人在球的上方   
            //   
            rbd = RBD_TOP;   
        }   
        else if (ballY > robotY) {   
            //   
            // 机器人在球的下方   
            //   
            rbd = RBD_BOTTOM;   
        }   
    }   
   
    //   
    // 分析机器人踢球的方向   
    //   
    {   
        if (rbd == RBD_LEFT) {   
            //   
            // 机器人在球的左边，踢球方向为 KD_5   
            //   
            direction = KD_5;   
        }   
        else if (rbd == RBD_RIGHT) {   
            //   
            // 机器人在球的右边，踢球方向为 KD_4   
            //   
            direction = KD_4;   
        }   
        else if (rbd == RBD_TOP) {   
            //   
            // 机器人在球的上方 6, 7, 8   
            // 机器人的 X 等于 球的 X 则踢的方向为 7   
            // 如果我方球门在 左边 - 机器人的 X 小于 球的 X 则踢的方向为 8   
            // 如果我方球门在 右边 - 机器人的 X 大于 球的 X 则踢的方向为 6   
            //   
            if (robotX == ballX)   
                direction = KD_7;   
            else if (robotX < ballX)  
                direction = KD_8;   
            else   
                direction = KD_6;   
   
        }   
        else if (rbd == RBD_BOTTOM) {   
            //   
            // 机器人在球的下方 1, 2, 3   
            // 机器人的 X 等于 球的 X 则踢的方向为 2   
            // 如果我方球门在 左边 - 机器人的 X 小于 球的 X 则踢的方向为 3   
            // 如果我方球门在 右边 - 机器人的 X 大于 球的 X 则踢的方向为 1   
            //   
            if (robotX == ballX)   
                direction = KD_2;   
            else if (robotX < ballX)   
                direction = KD_3;   
            else   
                direction = KD_1;   
        }   
    }   
}   
   
/** 
* 踢球 
* 将球往非球门区域方向使劲踢 
* @return == true 可以踢，并赋与此机器人的踢球动作 
*         == false 不可以踢，未进行任何操作，上一层跟据情况做其它处理 
*/ 
bool actKickBall (Robot &robot, const Environment &env){
	//Show("actKickBall");
	/*  
        A 区域内允许踢 2, 7, 3, 5, 8 三个角度  
            在以下条件下 "不允许" 踢 2, 7 两个角度  
            1. 机器人在球的上方，球在中线的上方  
            2. 机器人在球的下方，球在中线的下方  
  
            1, 4 两个方向不允许踢  
              
                *如果时间和精力允许考虑踢的线路是否会被阻碍物阻档导致改变方向射向我方球门  
  
        B 区域内允许踢 2, 3, 5, 7, 8  
            1, 4, 两个方向不允许踢  
  
        C 区域内允许踢 3, 5, 8  
            1, 2, 4, 6, 7 不允许踢  
  
        D 区域内允许踢 2, 3, 5, 7, 8  
            1, 4, 6 不允许踢  
     */   
    double ballX = env.currentBall.pos.x;   
    double ballY = env.currentBall.pos.y;   
    double centerY = FIELD_CENTER_Y;        // 球场的中心位置 Y   
    double robotX = robot.pos.x;   
    double robotY = robot.pos.y;   
   
    //   
    // 踢球所需要的信息   
    //   
    KickArea area;   
    KickDirection direction;   
    RobotToBallDirection rbd;   
    analyseKickInfo (robot, env, area, direction, rbd);   
   
    switch (area) {   
        case KA_A: {   
            if (direction == KD_1 || direction == KD_4)   
                return false;   
   
            if (direction == KD_2 || direction == KD_7) {   
                if (rbd == RBD_TOP && ballY > centerY)   
                    return false;   
                if (rbd == RBD_BOTTOM && ballY <= centerY)   
                    return false;   
            }   
        }   
        break;   
   
        case KA_B: {   
            if (direction == KD_1 || direction == KD_4)   
                return false;   
        }   
        break;   
   
        case KA_C: {   
            if (direction == KD_1 ||    
                direction == KD_2 ||    
                direction == KD_4 ||    
                direction == KD_6 ||    
                direction == KD_7) {   
                return false;   
            }   
        }   
        break;   
   
        case KA_D: {   
            if (direction == KD_1 ||   
                direction == KD_4 ||   
                direction == KD_6) {   
                return false;   
            }   
        }   
        break;   
    }    
    //   
    // 可以踢球   
    //   
    double targetX = 0;     // 球的目标点 X 轴   
    double targetY = 0;     // 球的目标点 Y 轴   
   
    if (rbd == RBD_BOTTOM) {   
        //   
        // 机器人在下方，向上踢球   
        //   
        if (direction == KD_1) {   
            //   
            // 向左上踢
			//
            targetX = FLEFTX - FIELD_WIDTH / 2;   
            
        }   
        else if (direction == KD_2) {   
            //   
            // 向上踢   
            //   
            targetX = FTOP + FIELD_HEIGHT / 2;   
        }   
        else if (direction == KD_3) {   
            //   
            // 向右上踢   
  
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
          
        }   
    }   
    else if (rbd == RBD_TOP) {   
        //   
        // 机器人在上方，向下踢球   
        //   
        if (direction == KD_6) {   
            //   
            // 向左下踢   
            //   
       
                targetX = FLEFTX - FIELD_WIDTH / 2;   
      
        }   
        else if (direction == KD_7) {   
            //   
            // 向下踢   
            //   
            targetX = FBOT - FIELD_HEIGHT / 2;   
        }   
        else if (direction == KD_8) {   
            //   
            // 向右下踢   
            //   
           
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
          
        }   
    }   
    else if (rbd == RBD_RIGHT) {   
        //   
        // 机器人在球的右边，向左踢   
        //   
        if (direction == KD_1 || direction == KD_4 || direction == KD_6)   
            targetX = FLEFTX - FIELD_WIDTH / 2;   
    }   
    else if (rbd == RBD_LEFT) {   
        //   
        // 机器人在球的左边，向右踢   
        //   
        if (direction == KD_3 || direction == KD_5 || direction == KD_8)   
            targetX = FRIGHTX + FIELD_WIDTH / 2;   
    }   
   
    //   
    // 因 kickBall 中的 x, y 点都是以实际情况下的点来确定，因此不能使用 transform   
    //   
    //transform (targetX, targetY);   
    //   
    /*  
                      
                    X  
                    |  
                    |      #  
                 *  |   *  
              #     |  
                    |  
              |-----|------|  
                 1      2  
  
            X 为目标点的 X  
            * 为球  
            # 为机器人  
  
            1. 第一种情况，机器人在球的左边，球在 X 的左边  
               球映射点的 Y 时，第一个点为 机器人，第二个点为 球  
            2. 第二种情况，机器人在球的右边，球在 X 的右边  
               球映射点的 Y 时，第一个点为 机器人，第二个点为 球  
              
            getMappedTargetY (机器人, 球, X);  
     */   
    
    targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
   
    actToPosition (robot, targetX, targetY);   
    return true;   
}  

/** 
* 抢球 
*/ 
void actReaveBall (Robot &robot){
	//Show("actReaveBall");
}  

/** 
* 传球 
*/ 
void actPassBall (Robot &robot){
	//Show("actPassBall");
}  

/** 
* 盯指定的敌方 
*/ 
void actBlockMan (Robot &robot, const OpponentRobot &opponent){
	actToPosition (robot, opponent.pos.x, opponent.pos.y); 
}   

///** 
// * 跑位 
// */ 
//void pointWaiting (Robot &robot); 
// 
///** 
// * 边界处理 
// */ 
//void boundProcess (Robot &robot); 
//

