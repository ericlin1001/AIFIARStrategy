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
#define ROBOT_DIAMETER ROBOT_INFO::LENGTH
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
       //
        addRole (new RoleLeftTopDefend ());     // PT_DEFEND_LEFT_TOP ���Ͻǵĺ���    
        addRole (new RoleLeftBotDefend ());     // PT_DEFEND_LEFT_BOT ���½ǵĺ���   
        addRole (new RoleRightTopDefend ());    // PT_DEFEND_RIGHT_TOP ���Ͻǵĺ���   
        addRole (new RoleRightBotDefend ());    // PF_DEFEND_RIGHT_BOT ���½ǵĺ��� 
		//
		addRole (new RoleTest ()); 
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
			for(int i=0;i<_roles.size();i++){
				role=_roles[i];
				if(role->getType()==type)return role;
			}
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
                                  const LastRole &lastRole,const Environment *env)   
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
        //cout<<" RoleGoalkeeper::strategy "<<endl;
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
        //   ??
		if (robot.GetDistanceTo(VecPosition(env->predictedBall.pos.x,env->predictedBall.pos.y)) <= (ROBOT_INFO::HALF_DIAGNOL+BALL_INFO::RADIUS)) {   
            //   
            // �����߳��᲻��ȷ���������Ա�ܿ���λ - �ȷ���һ�������ӵĲ���   
            //   
       
            ////   
            //// ����   
            ////   
            if (canShoot (robot.pos.x, robot.pos.y, env->currentBall.pos.x, env->currentBall.pos.y) == true) {   
              actShoot (robot, *env);   
              return;   
            }   
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
        if (term1 && (term2 || (term3 && (term4 && term5)))) {   
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
        if (targetY > GTOPY - ROBOT_DIAMETER / 2)   
            targetY = GTOPY - ROBOT_DIAMETER / 2;   
        if (targetY < GBOTY + ROBOT_DIAMETER / 2)   
            targetY = GBOTY + ROBOT_DIAMETER / 2;   
       
        actToPosition (robot, targetX, targetY);   
    }   
       
    //   
    // �ӻ�δ����Ļ��������ҳ���ָ��������Ļ�����   
    //   
    #define FIND_ROBOT(pointX, pointY)    return helpAssignRobots(robots,robotIndexs,lastRole,pointX,pointY);
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
                                   const LastRole &lastRole,const Environment *env)   
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
        //cout<<" RoleVanguardTop::strategy "<<endl;
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
    
       
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppSmallForbidX = OPP_SMALL_FORBID_ZONE_X;   
       
        if (x > oppSmallForbidX ) {   
            double tempY = 0;     
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
                                      const LastRole &lastRole,const Environment *env)   
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
       // cout<<" RoleVanguardBottom::strategy "<<endl;
		/*  
            ��ǰ���ɫ����  
            ��������Ϊ 13, 14, 15, 18, 19, 20  
                1. ��������������ʱ����� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��  
                2. ��һ�������������������ִ���������� ��ִ����������  
                   ������������ɫ���  
         */   
		Show("RoleVanguardBottom");
        BallArea area = areaInfo->getArea ();  
		Show(convertBallArea(area));
        if (area == BA_13 ||   
            area == BA_14 ||   
            area == BA_15 ||   
            area == BA_18 ||   
            area == BA_19 ||   
            area == BA_20) {   
            if (actKickBall (robot, *env) == false)   {
                actShoot (robot, *env);   
				Show("shoot");
			}
            return;   
        }   
       
        //   
        // ������� X ���ƶ�, Y ��Ϊ�°볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y - FIELD_HEIGHT / 4;   
       
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppSmallForbidX = OPP_SMALL_FORBID_ZONE_X;   
        if (x > oppSmallForbidX) {   
            double tempY = 0;     
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
                              const LastRole &lastRole,const Environment *env)   
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
        // cout<<" RoleAttack::strategy "<<endl;
		/* double ballX, ballY;
        ballX = env->predictedBall.pos.x;   
        ballY = env->predictedBall.pos.y;
		//
		VecPosition target;
		VecPosition cur=robot.get_position();
		VecPosition goal=VecPosition(FIELD_INFO::GOAL::getOppCenterX(),FIELD_INFO::GOAL::getOppCenterY());
		VecPosition ball=VecPosition(ballX,ballY);
		VecPosition dir=-(goal-ball);
		//target=(goal-ball).SetMagnitude(-(ROBOT_INFO::HALF_LENGTH+BALL_INFO::RADIUS))+ball;
		//
		VecPosition curdir=cur-ball;
		AngRad angle=curdir.GetDirection()-dir.GetDirection();
		if(fabs(angle)<PI/2*1/3){
			robot.ToPositionPD(ball+dir.SetMagnitude(BALL_INFO::RADIUS));
		}else{
			double len=BALL_INFO::RADIUS+ROBOT_INFO::HALF_LENGTH*1.4143;
			if(VecPosition::NormalizeAngle(angle)>0){
				curdir.Rotate(-PI/2);
			}else{
				curdir.Rotate(PI/2);
			}
			robot.ToPositionPD(ball+curdir.SetMagnitude(len));
		}*/
		
       /*  
            ������ɫ  
            �������� �з�С�����߶� ��Ӧ������  
                1. ��������������ʱ����� X ���ƶ�, Y ��Ϊ�򳡵��м�λ��  
                2. ��һ�������������������ִ����������  
         */   
		Show("RoleAttack");
        double ballX, ballY;   
        ballX = env->predictedBall.pos.x;   
        ballY = env->predictedBall.pos.y;   
       
        BallArea area = areaInfo->getArea ();   
		Show(convertBallArea(area));
        if (area == BA_9 || area == BA_10 || area == BA_14 || area == BA_15) {   
			Show("kick");
            actShoot (robot, *env);   
            return;   
        }else{
		
        //   
        // ������� X ���ƶ�, Y ��Ϊ�ϰ볡���м�λ��   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y;
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����Է�С���� X �ᣬ��ͣ���� �Է�С���� X ����   
        //   
        double oppForbidX = OPP_FORBID_ZONE_X;   
        
        if (x > oppForbidX ) {   
            double tempY = 0;   
         
            x = oppForbidX;   
        }   
       
        actToPosition (robot, x, y);   
		}
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // ����������ɫ   
    //   
       
    // public    
    long   
    RoleAttackDefend::assignRobots (const Robot *robots,   
                                    const vector <long> &robotIndexs,   
                                    const LastRole &lastRole,const Environment *env)   
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
      //cout<<" RoleAttackDefend::strategy "<<endl;
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
            area == BA_17  ||   
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
        x = env->predictedBall.pos.x;   
       
        //   
        // ��� X �����ҷ��볡������ X ���� X �� �ҷ��볡������ X   
        //   
        double defendX = FLEFTX + FIELD_WIDTH / 4;      // ����������Ĭ�� X   
       
        if (x > defendX ) {   
            double tempY = 0;  
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
                                      const LastRole &lastRole,const Environment *env)   
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
       // cout<<"RoleLeftTopDefend::strategy "<<endl;
		BallArea area = areaInfo->getArea ();   
        if (area == BA_1 || area == BA_6) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = FLEFTX + ROBOT_DIAMETER;   
        double defendY = DEFEND_LEFT_TOP_Y; 
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
                                      const LastRole &lastRole,const Environment *env)   
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
       //cout<<"RoleLeftBotDefend::strategy"<<endl;
		BallArea area = areaInfo->getArea ();   
        if (area == BA_11 || area == BA_16) {   
            if (actKickBall (robot, *env) == true)   
                return;   
        }   
       
        double defendX = FLEFTX + ROBOT_DIAMETER;   
        double defendY = DEFEND_LEFT_BOT_Y;   
       
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
                                      const LastRole &lastRole,const Environment *env)   
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
        //cout<<" RoleRightTopDefend::strategy"<<endl;
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
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // ��ǰ��ɫΪ���ض��ε����½ǵĺ�����ɫ   
        // ���ѡ��һ������ �����½� ����Ļ����˵��δ˽�ɫ   
        //   
        FIND_ROBOT (DEFEND_RIGHT_BOT_X, FBOT);   
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
       //cout<<"  RoleRightBotDefend::strategy"<<endl;
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
        actToPosition (robot, defendX, defendY);   
    }   
       


ASSIGNROBOT_MACRO(RoleTest){
	FIND_ROBOT (env->currentBall.pos.x,env->currentBall.pos.y);
}
STRATEGY_MACRO(RoleTest){
	ShootGoal(robot,*env);
	//EndProcess(robot,*env,VecPosition(env->currentBall.pos.x,env->currentBall.pos.y));
	//actToPosition(robot,110,90);
}