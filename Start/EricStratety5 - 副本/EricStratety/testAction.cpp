#include "stdafx.h"
#include "action.h"
/**************************************************************************************************** 
action.h ���������˽�ɫ����ͷ�ļ� 

Purpose: 
��ɫ����ʹ�õĶ��� 

author: 
yy_cn 

Created Time: 
2006-5-10 
****************************************************************************************************/ 

/** 
* robot �Ƿ�������� 
* robotX �����˵� X ���� 
* robotY �����˵� Y ���� 
* ballX ��� X ���� 
* ballY ��� Y ���� 
* ����Ҫ������ת�� 
* @return == true �������� 
* @return == false ���������� 
*/ 
bool canShoot (double robotX, double robotY, double ballX, double ballY){
	//Show("canShoot");
	if(robotX>ballX)return false;

	double targetX = OPP_GOAL_CENTER_X;   
    double targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
   
    //   
    // targetY Ϊ���� ������ �� �� ֮��Ƕ���� targetX �� Y ֵ   
    //   
    if (targetY < GTOPY && targetY > GBOTY)   
        return true;   
   
    return false; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ����ϵͳ���ṩ�����˽�ɫ��һϵͳ����֧�� 
// 
// 
// �����������ɻ�����������ϳɸ��ӵĶ��� 
// 

/** 
* ����С������ 
*/ 
void actVelocity (Robot &robot, int vl, int vr){
	robot.set_left_velocity(vl);
	robot.set_right_velocity(vr);
} 

//	/** 
//	 * ��������ĳ�������˶� 
//	 */ 
//	static void move (Robot &robot, BallDirection direction); 

/** 
* ԭ��������ָ���Ƕ� 
* @param -180  angle  180 
*/ 
void actTurn (Robot &robot, double angle){
	robot.TurnToAngle(angle);
}  

/** 
* ���������ƶ���ָ��λ�� 
*/ 
#include "GeometryR.h"
inline void actToPosition (Robot &robot, double x, double y){
	robot.ToPositionPD(VecPosition(x,y));
}  

// 
// �ɻ���������ɵĸ��Ӷ��� 
// 

/** 
* ���� 
* ����ǶȻ�λ����ȷ���ʹ���ƶ������ƶ������ʵ�λ�� 
*/ 
void actShoot (Robot &robot, const Environment &env)   
{   
    //   
    // ���� - ����������ͬ   
    // 1. ����������ǳ���������ٶ�Ϊ�е��٣���ʹ�����·����ܹ�׼ȷ������   
    //    ֱ���� �����˵����ĵ� �� ��ĵ��ĵ� �γɵ�һ��ֱ����Է������������ƶ�   
    //    ���ƶ���Ŀ�������Ϊһ���ȽϱȽ�Զ��λ�ã���ʱ������������ײ�������ٶ�����������ƶ�   
    //    ��������˵�ǰ�����겻�ʺ����ţ��򽫻������ƶ���һ�����ʵ������λ��   
    //   
    // 2. ������������һ���ľ��룬����ٶ�Ϊ���٣���ʹ�����·����ܹ�׼ȷ������   
    //    ����˶������������ˮƽ�ƶ��ķ����ܹ�����һ������   
    //    �Ҳ�������Ļ������ƶ��ķ���Ϊ�з�����   
    //   
       
    //   
    // ��ʱֻ���� 1 �����   
    //   
       
   
    //   
    // ���ţ���ʵ�ּ򵥷�����ֱ���Ի����������������ĵĽǶ���   
    //   
    // ��ʱ��Ļ����о�ȷ�ļ��㣬�������ˣ����������ĽǶȵ�ֱ���ϵĵ���   
    // ���ŽǶ��������ڵ�����������з�������   
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
        // �ǶȲ���ȷ���ƶ������˵����ʵ�λ�� - ����Է����ŷ�������ı���   
        //   
 
        targetX = ballX - BALL_DIAMETER;
        //   
        // �ƶ���Ŀ���Ϊ���ŵı߽�   
        //   
        double shootX = OPP_GOAL_CENTER_X;   
        double shootY = 0;//OPP_GOAL_CENTER_Y;   
        if (robot.pos.y < ballY) {   
            //   
            // ������������·�   
            //   
            shootY = GTOPY - BALL_DIAMETER - BALL_DIAMETER;   
        }   
        else {   
            //   
            // ������������Ϸ�   
            //   
            shootY = GBOTY + BALL_DIAMETER - BALL_DIAMETER;   
        }   
   
        //   
        // �Է���������Ϊ��һ���㣬��Ϊ�ڶ����㣬 targetX Ϊ��֪�� X �㣬��� targetY   
        //   
        targetY = getMappedTargetY (shootX, shootY, ballX, ballY, targetX);   
        if (targetX < FLEFTX || targetX > FRIGHTX || targetY < FBOT || targetY > FTOP) {   
            //   
            // �򿿽����ر߿�ֱ��ײ��   
            //   
            actToPosition (robot, ballX, ballY);   
            //actBezier2Reach (robot, ballX, ballY, 2.5);   
            return;   
        }   
   
        //   
        // �ƶ��� targetX, targetY ��   
        //   
        actToPosition (robot, targetX, targetY);   
        //actBezier2Reach (robot, targetX, targetY, 2.5);   
        return;   
    }   
   
    //   
    // �Ƕ���ȷ�����һ���ǳ�Զ��ӳ����ΪĿ����ƶ��ﵽ���ŵ�Ŀ��   
    // ���Ŀ����Զ������������Խ������������Խ��   
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
****** ���²��������ҷ�����볡Ϊ�ο�ֵ *******  
      **********************************  
  
          A     B          C      D  
        |--|---------|----------|---|  
        +---------------------------+  
        |            |              |  
       _|+++         |           +++|_  
      | |  +         |           +  | | ____ �е� centerY  
      |_|  +         |           +  |_|  
        |+++         |           +++|  
        |            |              |  
        +---------------------------+  
        <-�ҷ���         �з���->  
  
        +---------------------------+  
        |            |              |  
       _|+++         | 1  2  3   +++|_ - GTOPY  
      | |  +         | 4  *  5   +  | | ____ �е� centerY  
      |_|  +         | 6  7  8   +  |_|  
        |+++         |           +++|  - GBOTY  
        |            |              |  
        +---------------------------+  
        <-��                     ǰ->  
  
        1,2,3,4,5,6,7,8 ������λ��  
        * ���λ��  
  
                          ��  
        +---------------------------+  
        |            |              |  
       _|+++         |  1  2  3  +++|_   
   �� | |  +         |  4  *  5  +  | | ��  
      |_|  +         |  6  7  8  +  |_|  
        |+++         |           +++|  
        |            |              |  
        +---------------------------+  
                          ��  
          
        ����������� �Ϸ�: 1, 2, 3  
                     ��: 4  
                     �ҷ�: 5  
                     �·�: 6, 7, 8  
*/   
//   
// �����ж�ʱ���򳡷�Ϊ�ĸ�����   
//   
enum KickArea   
{   
    KA_A,   // A   
    KA_B,   // B   
    KA_C,   // C   
    KA_D,   // D   
}; // end enum KickArea   
   
//   
// ����ķ���   
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
// ����������ķ���   
//   
enum RobotToBallDirection   
{   
    RBD_TOP,   
    RBD_LEFT,   
    RBD_RIGHT,   
    RBD_BOTTOM,   
}; // end enum RobotToBallDirection   
   
//   
// ��������ʱ�������Ϣ   
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
    // �ȷ��������ĸ�����   
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
    // ����������������ĸ�����   0
    //   
    {   
        if (ballY == robotY) {   
            //   
            // ��� X ������ڻ����˵� X �������ҷ�����볡������������ ���   
            // ��� X ����С�ڻ����˵� X �������ҷ����Ұ볡������������ ���   
            //   
            if (ballX > robotX )
                rbd = RBD_LEFT;   
            else   
                rbd = RBD_RIGHT;   
        }   
        else if (ballY <= robotY) {   
            //   
            // ������������Ϸ�   
            //   
            rbd = RBD_TOP;   
        }   
        else if (ballY > robotY) {   
            //   
            // ������������·�   
            //   
            rbd = RBD_BOTTOM;   
        }   
    }   
   
    //   
    // ��������������ķ���   
    //   
    {   
        if (rbd == RBD_LEFT) {   
            //   
            // �������������ߣ�������Ϊ KD_5   
            //   
            direction = KD_5;   
        }   
        else if (rbd == RBD_RIGHT) {   
            //   
            // ������������ұߣ�������Ϊ KD_4   
            //   
            direction = KD_4;   
        }   
        else if (rbd == RBD_TOP) {   
            //   
            // ������������Ϸ� 6, 7, 8   
            // �����˵� X ���� ��� X ���ߵķ���Ϊ 7   
            // ����ҷ������� ��� - �����˵� X С�� ��� X ���ߵķ���Ϊ 8   
            // ����ҷ������� �ұ� - �����˵� X ���� ��� X ���ߵķ���Ϊ 6   
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
            // ������������·� 1, 2, 3   
            // �����˵� X ���� ��� X ���ߵķ���Ϊ 2   
            // ����ҷ������� ��� - �����˵� X С�� ��� X ���ߵķ���Ϊ 3   
            // ����ҷ������� �ұ� - �����˵� X ���� ��� X ���ߵķ���Ϊ 1   
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
* ���� 
* ������������������ʹ���� 
* @return == true �����ߣ�������˻����˵������� 
*         == false �������ߣ�δ�����κβ�������һ������������������ 
*/ 
bool actKickBall (Robot &robot, const Environment &env){
	//Show("actKickBall");
	/*  
        A ������������ 2, 7, 3, 5, 8 �����Ƕ�  
            ������������ "������" �� 2, 7 �����Ƕ�  
            1. ������������Ϸ����������ߵ��Ϸ�  
            2. ������������·����������ߵ��·�  
  
            1, 4 ��������������  
              
                *���ʱ��;����������ߵ���·�Ƿ�ᱻ�谭���赵���¸ı䷽�������ҷ�����  
  
        B ������������ 2, 3, 5, 7, 8  
            1, 4, ��������������  
  
        C ������������ 3, 5, 8  
            1, 2, 4, 6, 7 ��������  
  
        D ������������ 2, 3, 5, 7, 8  
            1, 4, 6 ��������  
     */   
    double ballX = env.currentBall.pos.x;   
    double ballY = env.currentBall.pos.y;   
    double centerY = FIELD_CENTER_Y;        // �򳡵�����λ�� Y   
    double robotX = robot.pos.x;   
    double robotY = robot.pos.y;   
   
    //   
    // ��������Ҫ����Ϣ   
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
    // ��������   
    //   
    double targetX = 0;     // ���Ŀ��� X ��   
    double targetY = 0;     // ���Ŀ��� Y ��   
   
    if (rbd == RBD_BOTTOM) {   
        //   
        // ���������·�����������   
        //   
        if (direction == KD_1) {   
            //   
            // ��������
			//
            targetX = FLEFTX - FIELD_WIDTH / 2;   
            
        }   
        else if (direction == KD_2) {   
            //   
            // ������   
            //   
            targetX = FTOP + FIELD_HEIGHT / 2;   
        }   
        else if (direction == KD_3) {   
            //   
            // ��������   
  
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
          
        }   
    }   
    else if (rbd == RBD_TOP) {   
        //   
        // ���������Ϸ�����������   
        //   
        if (direction == KD_6) {   
            //   
            // ��������   
            //   
       
                targetX = FLEFTX - FIELD_WIDTH / 2;   
      
        }   
        else if (direction == KD_7) {   
            //   
            // ������   
            //   
            targetX = FBOT - FIELD_HEIGHT / 2;   
        }   
        else if (direction == KD_8) {   
            //   
            // ��������   
            //   
           
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
          
        }   
    }   
    else if (rbd == RBD_RIGHT) {   
        //   
        // ������������ұߣ�������   
        //   
        if (direction == KD_1 || direction == KD_4 || direction == KD_6)   
            targetX = FLEFTX - FIELD_WIDTH / 2;   
    }   
    else if (rbd == RBD_LEFT) {   
        //   
        // �������������ߣ�������   
        //   
        if (direction == KD_3 || direction == KD_5 || direction == KD_8)   
            targetX = FRIGHTX + FIELD_WIDTH / 2;   
    }   
   
    //   
    // �� kickBall �е� x, y �㶼����ʵ������µĵ���ȷ������˲���ʹ�� transform   
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
  
            X ΪĿ���� X  
            * Ϊ��  
            # Ϊ������  
  
            1. ��һ��������������������ߣ����� X �����  
               ��ӳ���� Y ʱ����һ����Ϊ �����ˣ��ڶ�����Ϊ ��  
            2. �ڶ��������������������ұߣ����� X ���ұ�  
               ��ӳ���� Y ʱ����һ����Ϊ �����ˣ��ڶ�����Ϊ ��  
              
            getMappedTargetY (������, ��, X);  
     */   
    
    targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
   
    actToPosition (robot, targetX, targetY);   
    return true;   
}  

/** 
* ���� 
*/ 
void actReaveBall (Robot &robot){
	//Show("actReaveBall");
}  

/** 
* ���� 
*/ 
void actPassBall (Robot &robot){
	//Show("actPassBall");
}  

/** 
* ��ָ���ĵз� 
*/ 
void actBlockMan (Robot &robot, const OpponentRobot &opponent){
	actToPosition (robot, opponent.pos.x, opponent.pos.y); 
}   

///** 
// * ��λ 
// */ 
//void pointWaiting (Robot &robot); 
// 
///** 
// * �߽紦�� 
// */ 
//void boundProcess (Robot &robot); 
//

