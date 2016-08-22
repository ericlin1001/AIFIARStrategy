    /****************************************************************************************************  
    robotrole.cpp ���������˽�ɫԴ�ļ�  
      
    Purpose:  
        ��ɫ����ʹ�õĶ���  
      
    author:  
        yy_cn  
          
    Created Time:  
        2006-5-9  
    ****************************************************************************************************/   
    #include "stdafx.h"
    #include "area.h"   
    #include "action.h"   
    #include "robotrole.h"   

    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ��ɫ����   
    //   
       
    // public   
    RoleManager::RoleManager (void)   
        : _roles ()   
    {   
        addRole (new RoleGoalkeeper ());        // RT_GOALKEEPER - ����Ա��ɫ   
        addRole (new RoleAttack ());            // PT_ATTACK - ����   
        addRole (new RoleVanguardTop ());       // PT_VANGUARD_TOP - ������ǰ��   
        addRole (new RoleVanguardBottom ());    // PT_VANGUARD_BOTTOM - ������ǰ��   
        addRole (new RoleAttackDefend ());      // PT_ATTACK_DEFEND - �»���   
       
        addRole (new RoleLeftTopDefend ());     // PT_DEFEND_LEFT_TOP ���Ͻǵĺ���    
        addRole (new RoleLeftBotDefend ());     // PT_DEFEND_LEFT_BOT ���½ǵĺ���   
        addRole (new RoleRightTopDefend ());    // PT_DEFEND_RIGHT_TOP ���Ͻǵĺ���   
        addRole (new RoleRightBotDefend ());    // PF_DEFEND_RIGHT_BOT ���½ǵĺ���   
    }   
       
    // public   
    RoleManager::~RoleManager (void)   
    {   
        for_each (_roles.begin (), _roles.end (), delete_t <RobotRole> ());   
    }   
       
    // public   
    void   
    RoleManager::addRole (RobotRole *role)   
    {   
        if (role == 0) {   
            ASSERT (false);   
            return;   
        }   
        _roles.push_back (role);   
    }   
       
    // public   
    RobotRole *   
    RoleManager::getRole (RoleType type)   
    {   
        RobotRole *role = _roles[(int) type];   
        if (role == 0 || type != role->getType () || type == RT_UNKNOWN) {   
            ASSERT (false);   
        }   
       
        return role;   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ����Ա��ɫ   
    //   
       
    // public virtual   
    long   
    RoleGoalkeeper::assignRobots (const Robot *robots,   
                                  const vector <long> &robotIndexs,   
                                  const LastRole &lastRole)   
    {   
        return 0;   
    }   
       
    // public virtual   
    void   
    RoleGoalkeeper::strategy (Robot &robot,   
                              const AreaInfo *areaInfo,   
                              BallSpeed speed,   
                              BallDirection direction,   
                              BallPower power,   
                              GuardLeak leak,   
                              const Environment *env)   
    {   
        //   
        // ����Ա���Ų���   
        //   
        /*  
            A -> B -> C -> .... ���ȼ���ߵ�Ϊ A  
      
            A. ��������Ա�ȽϽ��ľ��룬�����Ƴ���֤��ȫ  
                ������  
                    1. ����Ա����ľ���ֻ�а�������˿�  
                       ʹ��������ŷ�������  
      
            B. ����Ҫ���أ�����Ա�˻ص�����ǰ�� GOAL_CENTER_X, GOAL_CENTER_Y λ�� - �Դ�ֱ�ķ�ʽ�ƶ�  
                ������  
                    1. ��δ�� 1, 6, 7, 11, 12, 16 ������  
                    2. ����ٶ�С�ڵ��� BS_LOW �е���  
                    3. ����ٶȴ��ڵ��� BS_MIDDLE_LOW �и���  
                    4. ��Ŀ���Ȩ�ڵз���  
                    5. ��ķ���Ϊ�ҷ����ŷ���  
      
                    1 & (2 || (3 & 4 & 5))  
      
           C. ��Ҫ���أ�����Ա�� x �ᱣ��������ǰ�� GOAL_CENTER_X  
              1. ������� 3, 8, 13, 18, ���ҷ������˶�����������ϴ�λ�ã�����λ�ã��������Ա Y ���϶�Ӧ�ĵ�  
                 �������ƶ����˵�  
                
              2. �����˵� Y �������� Y ���ƶ������Ҳ��������ŵ����� Y ֵ  
      
              Y �������� Y ���ƶ������Ҳ��������ŵ����� Y ֵ  
              ������� 1, 16 ����������Ավ�ڶ�Ӧ���������Ž���  
                ������  
                    1. A, B, ������������ʱ  
         */   
        //   
        // ���� A   
        //   
        if (getDistance (robot.pos.x, robot.pos.y, env->predictedBall.pos.x, env->predictedBall.pos.y) = ROBOT_DIAMETER / 2) {   
            //   
            // �����߳��᲻��ȷ���������Ա�ܿ���λ - �ȷ���һ�������ӵĲ���   
            //   
       
            ////   
            //// ����   
            ////   
            //if (canShoot (robot.pos.x, robot.pos.y, env->currentBall.pos.x, env->currentBall.pos.y) == true) {   
            //  actShoot (robot, *env);   
            //  return;   
            //}   
        }   
       
        //   
        // ���� B   
        //   
        BallArea area = areaInfo->getArea ();   
        bool term1 = false;   
        if (area != BA_1 && area != BA_6 && area != BA_7 && area != BA_11 && area != BA_12 && area != BA_16)   
            term1 = true;   
       
        bool term2 = false;   
        if (speed = BS_LOW)   
            term2 = true;   
       
        bool term3 = false;   
        if (speed >= BS_MIDDLE_LOW)   
            term3 = true;   
       
        bool term4 = false;   
        if (power == BP_OPPONENT)   
            term4 = true;   
       
        bool term5 = false;   
        if (direction != BD_LEFT_TOP && direction != BD_LEFT && direction != BD_LEFT_BOTTOM)   
            term5 = true;   
       
        //   
        // 1 & (2 || (3 & 4 & 5))   
        //   
        if (term1 && (term2 || (term3 && term4 && term5))) {   
            //   
            // ��������Ավ����λ���а�������˵�ƫ��   
            //   
            double x = GOAL_CENTER_X;   
            double y = GOAL_CENTER_Y;   
           
            ////   
            //// �������Ա��ǰ�� �� (X, Y) �� 1/4 �������˵ķ�Χ������Ҫ�ƶ�   
            ////   
            //double pointX1 = x - ROBOT_DIAMETER / 4;   
            //double pointY1 = y + ROBOT_DIAMETER / 4;   
            //double pointX2 = x + ROBOT_DIAMETER / 4;   
            //double pointY2 = y - ROBOT_DIAMETER / 4;   
       
            //transform (pointX1, pointY1);   
            //transform (pointX2, pointY2);   
            //   
            //if (robot.pos.x > pointX1 && robot.pos.x  pointX2 &&   
            //  robot.pos.y  pointY1 && robot.pos.y > pointY2) {   
            //  //   
            //  // ������������Է����ŵĽǶ�   
            //  // TODO:actTrun ��������ȷ��������   
            //  //   
            //  return;   
            //}   
       
            //   
            // �ƶ����е�λ�� - �Դ�ֱ�ķ�ʽ�ƶ�   
            //   
            double targetX = GOAL_CENTER_X;   
            double targetY = GOAL_CENTER_Y;   
            transform (targetX, targetY);   
       
            //if (robot.pos.x > targetX + 1 || robot.pos.x  targetX - 1) {   
                //actToPosition (robot, targetX, robot.pos.y);   
            //  return;   
            //}   
            //if (robot.pos.y > targetY + 1 || robot.pos.y  targetY - 1) {   
                actToPosition (robot, targetX, targetY);   
            //  return;   
            //}   
       
            //transform (x, y);   
            //actToPosition (robot, x, y);   
            return;   
        }   
       
        //   
        // ���� C   
        //   
        double targetX = GOAL_CENTER_X,   
               targetY = 0;   
        transform (targetX, targetY);   
       
        if ((area == BA_3 || area == BA_8 || area == BA_13 || area == BA_18) &&   
            (direction == BD_LEFT_TOP || direction == BD_LEFT || direction == BD_LEFT_BOTTOM)) {   
            targetY = getMappedTargetY (env->lastBall.pos.x,   
                                        env->lastBall.pos.y,   
                                        env->currentBall.pos.x,   
                                        env->currentBall.pos.y,   
                                        targetX);   
        }   
        else {   
            targetY = env->predictedBall.pos.y;   
        }   
       
        // �ƶ����� Y ���곬�����ŵ� Y ����ʱ�� Y �����Ϊ���ŵ� Y ����   
        //   
        if (targetY > GTOPY + ROBOT_DIAMETER / 2)   
            targetY = GTOPY + ROBOT_DIAMETER / 2;   
        if (targetY  GBOTY - ROBOT_DIAMETER / 2)   
            targetY = GBOTY - ROBOT_DIAMETER / 2;   
       
        actToPosition (robot, targetX, targetY);   
    }   
       
    //   
    // �ӻ�δ����Ļ��������ҳ���ָ��������Ļ�����   
    //   
    #define FIND_ROBOT(pointX, pointY)                                                  \   
        do {                                                                            \   
            long index = robotIndexs[0];                                                \   
            double distance = 9999;     /* �����ϴ�ѡ�����̾�������˵ľ��� */     \   
                                                                                        \   
            double goalX = pointX;      /* �򳡵��ұ߽�   */                              \   
            double goalY = pointY;      /* �����ϱ߽� */                             \   
            /**/                                                                        \   
            /* ���������ҷ���������ʱ���ǵģ���Ҫת�� */                              \   
            /**/                                                                        \   
            transform (goalX, goalY);                                                   \   
                                                                                        \   
            /**/                                                                        \   
            /* ��δ����Ļ������ҳ�����ʵĻ����� */                                 \   
            /**/                                                                        \   
            typedef vector <long>::const_iterator iterator;                               \   
            iterator itend = robotIndexs.end ();                                        \   
            for (iterator it = robotIndexs.begin (); it != itend; ++it) {               \   
                if (lastRole.role[(*it)] == getType ()) {                               \   
                    /**/                                                                \   
                    /* ��һ�η���Ľ�ɫ�а�����ǰ��Ҫ����Ľ�ɫ */                      \   
                    /* Ϊ�˱�֤��ɫִ������������ԣ�ʹ��ͬ���Ļ����������δ˽�ɫ */ \   
                    /**/                                                                \   
                    index = *it;                                                        \   
                    break;                                                              \   
                }                                                                       \   
                                                                                        \   
                /**/                                                                    \   
                /* ��õ�ǰ�������������Ͻǵľ��� */                                  \   
                /**/                                                                    \   
                double tempDe = getDistance (robots[(*it)].pos.x, robots[(*it)].pos.y, goalX, goalY);   \   
                if (tempDe  distance) {                                             \   
                    index = *it;                                                        \   
                    distance = tempDe;                                                  \   
                }                                                                       \   
            }                                                                           \   
                                                                                        \   
            return index;                                                               \   
        }                                                                               \   
        while (0)                                                                       \   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ��ǰ���ɫ   
    //   
    // ���� 3, 4, 5, 8, 9, 10 �����ڴ������ڽ�����з��򳡷�����   
    // ���������߸��м��������Ա   
    //   
       
    // public   
    long   
    RoleVanguardTop::assignRobots (const Robot *robots,   
                                   const vector <long> &robotIndexs,   
                                   const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ�������ε���ǰ���ɫ   
        // ���ѡ��һ������ �����Ͻ� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (FRIGHTX, FTOP);   
    }   
       
    // public   
    void   
    RoleVanguardTop::strategy (Robot &robot,   
                               const AreaInfo *areaInfo,   
                               BallSpeed speed,   
                               BallDirection direction,   
                               BallPower power,   
                               GuardLeak leak,   
                               const Environment *env)   
    {   
        /*  
            ��ǰ���ɫ����  
            ��������Ϊ 3, 4, 5, 8, 9, 10  
                1. ��������������ʱ����� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��  
                2. ��һ�������������������ִ���������� ��ִ����������  
                   ������������ɫ���  
         */   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_3 ||   
            area == BA_4 ||   
            area == BA_5 ||   
            area == BA_8 ||   
            area == BA_9 ||   
            area == BA_10) {   
            //if (actKickBall (robot, *env) == false)   
                actShoot (robot, *env);   
            return;   
        }   
       
        //   
        // ������� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y + FIELD_HEIGHT / 4;   
        transform (x, y);   
       
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppSmallForbidX = OPP_SMALL_FORBID_ZONE_X;   
       
        BallField fieldInfo = analyseFieldInfo ();   
        if ((x > oppSmallForbidX && fieldInfo == BF_IS_LEFT) || (x  oppSmallForbidX && fieldInfo == BF_IS_RIGHT)) {   
            double tempY = 0;   
            transform (oppSmallForbidX, tempY);   
            x = oppSmallForbidX;   
        }   
       
        actToPosition (robot, x, y);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ��ǰ���ɫ   
    //   
       
    // public   
    long   
    RoleVanguardBottom::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ�������ε���ǰ���ɫ   
        // ���ѡ��һ������ �����Ͻ� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (FRIGHTX, FBOT);   
    }   
       
    void   
    RoleVanguardBottom::strategy (Robot &robot,   
                                  const AreaInfo *areaInfo,   
                                  BallSpeed speed,   
                                  BallDirection direction,   
                                  BallPower power,   
                                  GuardLeak leak,   
                                  const Environment *env)   
    {   
        /*  
            ��ǰ���ɫ����  
            ��������Ϊ 13, 14, 15, 18, 19, 20  
                1. ��������������ʱ����� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��  
                2. ��һ�������������������ִ���������� ��ִ����������  
                   ������������ɫ���  
         */   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_13 ||   
            area == BA_14 ||   
            area == BA_15 ||   
            area == BA_18 ||   
            area == BA_19 ||   
            area == BA_20) {   
            if (actKickBall (robot, *env) == false)   
                actShoot (robot, *env);   
            return;   
        }   
       
        //   
        // ������� X ���ƶ�, Y ��Ϊ�°볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y - FIELD_HEIGHT / 4;   
        transform (x, y);   
       
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppSmallForbidX = OPP_SMALL_FORBID_ZONE_X;   
       
        BallField fieldInfo = analyseFieldInfo ();   
        if ((x > oppSmallForbidX && fieldInfo == BF_IS_LEFT) || (x  oppSmallForbidX && fieldInfo == BF_IS_RIGHT)) {   
            double tempY = 0;   
            transform (oppSmallForbidX, tempY);   
            x = oppSmallForbidX;   
        }   
       
        actToPosition (robot, x, y);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // �������ε�������ɫ   
    //   
       
    // public   
    long   
    RoleAttack::assignRobots (const Robot *robots,   
                              const vector <long> &robotIndexs,   
                              const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ�������ε�������ɫ   
        // ���ѡ��һ������ �з����� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (OPP_GOAL_CENTER_X, OPP_GOAL_CENTER_Y);   
    }   
       
    // public   
    void   
    RoleAttack::strategy (Robot &robot,   
                          const AreaInfo *areaInfo,   
                          BallSpeed speed,   
                          BallDirection direction,   
                          BallPower power,   
                          GuardLeak leak,   
                          const Environment *env)   
    {   
        /*  
            ������ɫ  
            �������� �з�С�����߶� ��Ӧ������  
                1. ��������������ʱ����� X ���ƶ�, Y ��Ϊ�򳡵��м�λ��  
                2. ��һ�������������������ִ����������  
         */   
        double ballX, ballY;   
        ballX = env->predictedBall.pos.x;   
        ballY = env->predictedBall.pos.y;   
       
        BallArea area = areaInfo->getArea ();   
        if (area == BA_9 || area == BA_10 || area == BA_14 || area == BA_15) {   
            actShoot (robot, *env);   
            return;   
        }   
       
        //   
        // ������� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y;   
        transform (x, y);   
       
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppForbidX = OPP_FORBID_ZONE_X;   
       
        BallField fieldInfo = analyseFieldInfo ();   
        if ((x > oppForbidX && fieldInfo == BF_IS_LEFT) || (x  oppForbidX && fieldInfo == BF_IS_RIGHT)) {   
            double tempY = 0;   
            transform (oppForbidX, tempY);   
            x = oppForbidX;   
        }   
       
        actToPosition (robot, x, y);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ����������ɫ   
    //   
       
    // public    
    long   
    RoleAttackDefend::assignRobots (const Robot *robots,   
                                    const vector <long> &robotIndexs,   
                                    const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ�������εĻ�����ɫ   
        // ���ѡ��һ������ �ҷ����� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (FORBIDDEN_ZONE_X, FIELD_CENTER_Y);   
    }   
       
    // public   
    void   
    RoleAttackDefend::strategy (Robot &robot,   
                                const AreaInfo *areaInfo,   
                                BallSpeed speed,   
                                BallDirection direction,   
                                BallPower power,   
                                GuardLeak leak,   
                                const Environment *env)   
    {   
        /*  
            ����������ɫ  
            ��������Ϊ 1, 2, 3, 6, 7, 8, 11, 12, 13, 16, 17, 18  
                1. ��������������ʱ����� Y ���ƶ�, X ��Ϊ�ҷ��볡���м�λ��  
                2. ��һ�������������������ִ���������� ��ִ����������  
         */   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_1 ||   
            area == BA_2 ||   
            area == BA_6 ||   
            area == BA_7 ||   
            area == BA_11 ||   
            area == BA_12 ||   
            area == BA_16 ||   
            area == BA_17 ||   
            area == BA_3 ||   
            area == BA_8 ||   
            area == BA_13 ||   
            area == BA_18) {   
            actKickBall (robot, *env);   
            return;   
        }   
       
        //   
        // ������� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y;   
        transform (x, y);   
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����ҷ��볡������ X ���� X �� �ҷ��볡������ X   
        //   
        double defendX = FLEFTX + FIELD_WIDTH / 4;      // ����������Ĭ�� X   
       
        BallField fieldInfo = analyseFieldInfo ();   
        if ((x > defendX && fieldInfo == BF_IS_LEFT) || (x  defendX && fieldInfo == BF_IS_RIGHT)) {   
            double tempY = 0;   
            transform (defendX, tempY);   
            x = defendX;   
        }   
       
        actToPosition (robot, x, y);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    //�����ͽ�ɫ - ���Ͻǵĺ���   
    //   
    // public   
    long   
    RoleLeftTopDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ���ض��ε����Ͻǵĺ�����ɫ   
        // ���ѡ��һ������ �����Ͻ� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (FLEFTX, FTOP);   
    }   
       
    void   
    RoleLeftTopDefend::strategy (Robot &robot,   
                                  const AreaInfo *areaInfo,   
                                  BallSpeed speed,   
                                  BallDirection direction,   
                                  BallPower power,   
                                  GuardLeak leak,   
                                  const Environment *env)   
    {   
        //   
        // ���� 1, 6 ������ʱ��������������������һֱ������ �������ϵ�����λ��   
        //   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_1 || area == BA_6) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = FLEFTX - ROBOT_DIAMETER / 2;   
        double defendY = DEFEND_LEFT_TOP_Y;   
        transform (defendX, defendY);   
        actToPosition (robot, defendX, defendY);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    //�����ͽ�ɫ - ���½ǵĺ���   
    //   
    // public   
    long   
    RoleLeftBotDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ���ض��ε����Ͻǵĺ�����ɫ   
        // ���ѡ��һ������ �����Ͻ� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (FLEFTX, FBOT);   
    }   
       
    void   
    RoleLeftBotDefend::strategy (Robot &robot,   
                                  const AreaInfo *areaInfo,   
                                  BallSpeed speed,   
                                  BallDirection direction,   
                                  BallPower power,   
                                  GuardLeak leak,   
                                  const Environment *env)   
    {   
        //   
        // ���� 11, 16 ������ʱ��������������������һֱ������ �������ϵ�����λ��   
        //   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_11 || area == BA_16) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = FLEFTX - ROBOT_DIAMETER / 2;   
        double defendY = DEFEND_LEFT_BOT_Y;   
        transform (defendX, defendY);   
        actToPosition (robot, defendX, defendY);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    //�����ͽ�ɫ - ���Ͻǵĺ���   
    //   
    // public   
    long   
    RoleRightTopDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ���ض��ε����Ͻǵĺ�����ɫ   
        // ���ѡ��һ������ �����Ͻ� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (DEFEND_RIGHT_TOP_X, FTOP);   
    }   
       
    void   
    RoleRightTopDefend::strategy (Robot &robot,   
                                  const AreaInfo *areaInfo,   
                                  BallSpeed speed,   
                                  BallDirection direction,   
                                  BallPower power,   
                                  GuardLeak leak,   
                                  const Environment *env)   
    {   
        //   
        // ���� 2, 7 ������ʱ��������������������һֱ������ �������ϵ�����λ��   
        //   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_2 || area == BA_7) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = DEFEND_RIGHT_TOP_X;   
        double defendY = DEFEND_RIGHT_TOP_Y;   
        transform (defendX, defendY);   
        actToPosition (robot, defendX, defendY);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    //�����ͽ�ɫ - ���½ǵĺ���   
    //   
    // public   
    long   
    RoleRightBotDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole)   
    {   
        //   
        // ��ǰ��ɫΪ���ض��ε����½ǵĺ�����ɫ   
        // ���ѡ��һ������ �����½� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (DEFEND_RIGHT_TOP_X, FBOT);   
    }   
       
    void   
    RoleRightBotDefend::strategy (Robot &robot,   
                                  const AreaInfo *areaInfo,   
                                  BallSpeed speed,   
                                  BallDirection direction,   
                                  BallPower power,   
                                  GuardLeak leak,   
                                  const Environment *env)   
    {   
        //   
        // ���� 12, 17 ������ʱ��������������������һֱ������ �������ϵ�����λ��   
        //   
        BallArea area = areaInfo->getArea ();   
        if (area == BA_12 || area == BA_17) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = DEFEND_RIGHT_BOT_X;   
        double defendY = DEFEND_RIGHT_BOT_Y;   
        transform (defendX, defendY);   
        actToPosition (robot, defendX, defendY);   
    }   
       


