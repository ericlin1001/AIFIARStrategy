/****************************************************************************************************  
action.h ���������˽�ɫ����ͷ�ļ�  
  
Purpose:  
    ��ɫ����ʹ�õĶ���  
  
author:  
    yy_cn  
      
Created Time:  
    2006-5-10  
****************************************************************************************************/   
   
#include "action.h"   
   
////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// ����ϵͳ���ṩ�����˵�һϵͳ����֧��   
//   
   
//   
// actVelocity   
//   
void actVelocity (Robot &robot, int vl, int vr)   
{   
    if (vr > 125)   
        vr = 125;   
    if (vl > 125)   
        vl = 125;   
    if (vr < -125)   
        vr = -125;   
    if (vl < -125)   
        vl = -125;   
   
    robot.velocityLeft  = vl;   
    robot.velocityRight = vr;   
}   
   
//   
// move   
//   
//void move (Robot &robot, BallDirection direction)   
//{   
//   
//}   
   
//   
// turn   
//   
void actTurn (Robot &robot, double angle)   
{   
    int theta_e, vl, vr;   
    theta_e = (int) angle - (int) robot.rotation;      
       
    while (theta_e > 180)   
        theta_e -= 360;   
   
    while (theta_e < -180)   
        theta_e += 360;   
   
    if (theta_e < -90)   
        theta_e += 180;   
    else if (theta_e > 90)   
        theta_e -= 180;   
   
    if (abs(theta_e) > 50) {   
        vl = (int) (-9./90.0 * (double)theta_e);   
        vr = (int) (9./90.0 * (double)theta_e);   
    }   
    else if (abs(theta_e) > 20)  {   
        vl = (int) (-11.0/90.0 * (double)theta_e);   
        vr = (int) (11.0/90.0 * (double)theta_e);   
    }   
   
    if (vl  0)   
        vl = 0;   
    if (vr  0)   
        vr = 0;   
   
    actVelocity (robot, vl, vr);   
}   
   
//   
// toPosition   
//   
void actToPosition (Robot &robot, double x, double y)   
{   
    double desired_angle = 0,   
           theta_e = 0,   
           d_angle = 0;   
    int vl,   
        vr,   
        vc = 200;   
   
    double dx, dy, d_e, Ka = 1.0;//10.0/90.0;   
   
    //   
    // ���㵽Ŀ��λ�õ�ֱ�߾���   
    //   
    d_e = getDistance (robot.pos.x, robot.pos.y, x, y);   
   
    //   
    // ���㵱ǰλ����Ŀ������λ��   
    //   
    dx = x - robot.pos.x;   
    dy = y - robot.pos.y;   
   
    //   
    // ���㵱ǰλ�õ�Ŀ���ĽǶ�   
    //   
    if (dx == 0 && dy == 0)   
        desired_angle = 90;   
    else   
        desired_angle = 180. / PI * atan2((double)(dy), (double)(dx));   
   
    //   
    // ��ǰ��������Ŀ��ļн�   
    //   
    theta_e = desired_angle - robot.rotation;   
       
    while (theta_e > 180)   
        theta_e -= 360;   
   
    while (theta_e  -180)   
        theta_e += 360;   
   
    //if (d_e > 100.)    
    //  Ka = 17. / 90.;         // 0.19   
    //else if (d_e > 50)   
    //  Ka = 19. / 90.;         // 0.21   
    //else if (d_e > 30)   
    //  Ka = 21. / 90.;         // 0.23   
    //else if (d_e > 20)   
    //  Ka = 23. / 90.;         // 0.25   
    //else    
    //  Ka = 25. / 90.;         // 0.27   
   
    //if (d_e  10.0 && d_e > 5.0) {   
    //  Ka = 0.1;   
    //  vc = 70;   
    //}   
    //else    
    if (d_e  10.0 && d_e > 5.0) {   
        vc = 40;   
    }   
    else if (d_e  4.0 && d_e > 2.0) {   
        Ka = 0.1;   
        vc = 30;   
    }   
    else if (d_e  2.0) {   
        Ka = 0.1;   
        vc = 20;   
    }   
    else if (d_e  1.0) {   
        Ka = 0.1;   
        vc = 0;   
    }   
    //if (d_e  3.0 && d_e > 2.0) {   
    //  Ka = 0.1;   
    //  vc /= 20;   
    //}   
    //else if (d_e  2.0 && d_e > 1.0) {   
    //  Ka = 0.1;   
    //  vc /= 50;   
    //}   
    //else if (d_e  1.0) {   
    //  Ka = 0.1;   
    //  vc /= 100;   
    //}   
   
    if (theta_e > 95 || theta_e  -95) {   
        theta_e += 180;   
           
        if (theta_e > 180)    
            theta_e -= 360;   
        if (theta_e > 80)   
            theta_e = 80;   
        if (theta_e  -80)   
            theta_e = -80;   
   
        //if (d_e  5.0 && abs(theta_e)  40)   
        //  Ka = 0.1;   
   
        vr = (int) (-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);   
        vl = (int) (-vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);   
    }      
    else if (theta_e  85. && theta_e > -85.) {   
        //if (d_e  5.0 && abs(theta_e)  40)   
        //  Ka = 0.1;   
   
        vr = (int) (vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) + Ka * theta_e);   
        vl = (int) (vc * (1.0 / (1.0 + exp(-3.0 * d_e)) - 0.3) - Ka * theta_e);   
    }   
    else {   
        vr = (int) (+.1 * theta_e);//(int) (+.17 * theta_e);   
        vl = (int) (-.1 * theta_e);//(int) (-.17 * theta_e);   
    }   
   
    actVelocity (robot, vl, vr);   
}   
   
//   
// shoot   
//   
   
bool canShoot (double robotX, double robotY, double ballX, double ballY)   
{   
    /*  
        +---------------------------+  
        |                           |  
        |-            1  2  3      -|- GTOPY          
        | |           4  *  5     | | <- ����з�����  
        |-            6  7  8      -|- GBOTY  
        |                           |  
        +---------------------------+  
        <-��                     ǰ->  
  
        1,2,3,4,5,6,7,8 ������λ��  
        * ���λ��  
     */   
    //   
    // ��������˵� X �������� X ������ӽ��Է�����˵�������������ŵķ�����   
    // ����ֱ�����ţ���Ҫ�ܵ���� X ������ӽ��Է����ŵ�����λ��   
    // �������� 3 5 8 λ�õ����ֱ�ӷ��ز�������   
    //   
    if (analyseFieldInfo () == BF_IS_LEFT && robotX > ballX) {   
        //   
        // �ҷ�����볡���з��������Ұ볡   
        // �����˵� X ����ҪС���������ſ���ֱ������   
        //   
        return false;   
    }   
    else if (analyseFieldInfo () == BF_IS_RIGHT && robotX  ballX) {   
        //   
        // �ҷ����Ұ볡���з���������볡   
        // �����˵� X ����Ҫ�����������ſ���ֱ������   
        //   
        return false;   
    }   
   
    //   
    // ���ݻ��������꣬������������γɵ�ֱ��ӳ�䵽�Է����� Y λ�õĵ�   
    // �Ƿ������ŷ�Χ����ȷ���Ƿ����ֱ������   
    //   
    double targetX = OPP_GOAL_CENTER_X;   
    double targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
   
    //   
    // targetY Ϊ���� ������ �� �� ֮��Ƕ���� targetX �� Y ֵ   
    //   
    if (targetY  GTOPY && targetY > GBOTY)   
        return true;   
   
    return false;   
}   
   
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
        if (analyseFieldInfo () == BF_IS_LEFT) {   
            //   
            // �ҷ�����볡���ƶ��������ߵ�һ����λ��   
            //   
            targetX = ballX - BALL_DIAMETER;   
        }   
        else {   
            //   
            // �ҷ����Ұ볡���ƶ�������ұߵ�һ����λ��   
            //   
            targetX = ballX + BALL_DIAMETER;   
        }   
   
        //   
        // �ƶ���Ŀ���Ϊ���ŵı߽�   
        //   
        double shootX = OPP_GOAL_CENTER_X;   
        double shootY = 0;//OPP_GOAL_CENTER_Y;   
        if (robot.pos.y  ballY) {   
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
   
        transform (shootX , shootY);   
   
        //   
        // �Է���������Ϊ��һ���㣬��Ϊ�ڶ����㣬 targetX Ϊ��֪�� X �㣬��� targetY   
        //   
        targetY = getMappedTargetY (shootX, shootY, ballX, ballY, targetX);   
        if (targetX  FLEFTX || targetX > FRIGHTX || targetY  FBOT || targetY > FTOP) {   
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
    transform (targetX, targetY);   
   
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
   
    BallField fieldInfo = analyseFieldInfo ();   
   
    //   
    // �ȷ��������ĸ�����   
    //   
    {   
        double aLeftX = FLEFTX,   
               bLeftX = FORBID_ZONE_X,   
               cLeftX = FIELD_CENTER_Y,   
               dLeftX = OPP_FORBID_ZONE_X,   
               dRightX = FRIGHTX;   
   
        double tempY = 0;   
   
        //   
        // �� X,Y ת��Ϊʵ������µ�����   
        //   
        transform (aLeftX, tempY);   
        transform (bLeftX, tempY);    
        transform (cLeftX, tempY);   
        transform (dLeftX, tempY);   
        transform (dRightX, tempY);   
   
        if ((aLeftX = ballX && ballX = bLeftX) || (aLeftX >= ballX && ballX >= bLeftX))   
            area = KA_A;   
        else if ((bLeftX = ballX && ballX = cLeftX) || (bLeftX >= ballX && ballX >= cLeftX))   
            area = KA_B;   
        else if ((cLeftX = ballX && ballX = dLeftX) || (cLeftX >= ballX && ballX >= dLeftX))   
            area = KA_C;   
        else if ((dLeftX = ballX && ballX = dRightX) || (dLeftX >= ballX && ballX >= dRightX))   
            area = KA_D;   
    }   
   
    //   
    // ����������������ĸ�����   
    //   
    {   
        if (ballY == robotY) {   
            //   
            // ��� X ������ڻ����˵� X �������ҷ�����볡������������ ���   
            // ��� X ����С�ڻ����˵� X �������ҷ����Ұ볡������������ ���   
            //   
            if ((ballX > robotX && fieldInfo == BF_IS_LEFT) ||   
                (ballX  robotX && fieldInfo == BF_IS_LEFT))   
                rbd = RBD_LEFT;   
            else   
                rbd = RBD_RIGHT;   
        }   
        else if (ballY  robotY) {   
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
            // ����ҷ������� �ұ� - �����˵� X ���� ��� X ���ߵķ���Ϊ 8   
            //   
            if (robotX == ballX)   
                direction = KD_7;   
            else if ((robotX  ballX && fieldInfo == BF_IS_LEFT) ||   
                     (robotX > ballX && fieldInfo == BF_IS_RIGHT))   
                direction = KD_8;   
            else   
                direction = KD_6;   
   
        }   
        else if (rbd == RBD_BOTTOM) {   
            //   
            // ������������·� 1, 2, 3   
            // �����˵� X ���� ��� X ���ߵķ���Ϊ 2   
            // ����ҷ������� ��� - �����˵� X С�� ��� X ���ߵķ���Ϊ 3   
            // ����ҷ������� �ұ� - �����˵� X ���� ��� X ���ߵķ���Ϊ 3   
            //   
            if (robotX == ballX)   
                direction = KD_2;   
            else if ((robotX  ballX && fieldInfo == BF_IS_LEFT) ||   
                     (robotX > ballX && fieldInfo == BF_IS_RIGHT))   
                direction = KD_3;   
            else   
                direction = KD_1;   
        }   
    }   
}   
   
bool actKickBall (Robot &robot, const Environment &env)   
{   
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
                if (rbd == RBD_BOTTOM && ballY  centerY)   
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
   
    BallField fieldInfo = analyseFieldInfo ();   
   
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
            if (fieldInfo == BF_IS_LEFT)   
                targetX = FLEFTX - FIELD_WIDTH / 2;   
            else   
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
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
            //   
            if (fieldInfo == BF_IS_LEFT)   
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
            else   
                targetX = FLEFTX - FIELD_WIDTH / 2;   
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
            if (fieldInfo == BF_IS_LEFT)   
                targetX = FLEFTX - FIELD_WIDTH / 2;   
            else   
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
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
            if (fieldInfo == BF_IS_LEFT)   
                targetX = FRIGHTX + FIELD_WIDTH / 2;   
            else   
                targetX = FLEFTX - FIELD_WIDTH / 2;   
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
    if ((robotX > ballX && ballX > targetX) || (robotX  ballX && ballX  targetX))   
        targetY = getMappedTargetY (robotX, robotY, ballX, ballY, targetX);   
    else   
        targetY = getMappedTargetY (ballX, ballY, robotX, robotY, targetX);   
    actToPosition (robot, targetX, targetY);   
    return true;   
}   
   
//   
// boundProcess   
//   
void actBoundProcess (Robot &robot)   
{   
       
}   
   
//   
// passBall   
//   
void actPassBall (Robot &robot)   
{   
       
}   
   
//   
// blockMan   
//   
void actBlockMan (Robot &robot, const OpponentRobot &opponent)   
{   
    actToPosition (robot, opponent.pos.x, opponent.pos.y);   
}   
   
////   
//// pointWaiting   
////       
//void pointWaiting (Robot &robot)   
//{   
//     
//}   
//   
////   
//// reaveBall   
////   
//void reaveBall (Robot &robot)   
//{   
//     
//}  