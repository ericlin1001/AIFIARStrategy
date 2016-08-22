    /****************************************************************************************************  
    robotrole.cpp 艾数机器人角色源文件  
      
    Purpose:  
        角色可以使用的动作  
      
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
    // 角色管理   
    //   
       
    // public   
    RoleManager::RoleManager (void)   
        : _roles ()   
    {   
        addRole (new RoleGoalkeeper ());        // RT_GOALKEEPER - 守门员角色   
        addRole (new RoleAttack ());            // PT_ATTACK - 助攻   
        addRole (new RoleVanguardTop ());       // PT_VANGUARD_TOP - 进攻上前锋   
        addRole (new RoleVanguardBottom ());    // PT_VANGUARD_BOTTOM - 进攻下前锋   
        addRole (new RoleAttackDefend ());      // PT_ATTACK_DEFEND - 下护卫   
       //
        addRole (new RoleLeftTopDefend ());     // PT_DEFEND_LEFT_TOP 左上角的后卫    
        addRole (new RoleLeftBotDefend ());     // PT_DEFEND_LEFT_BOT 左下角的后卫   
        addRole (new RoleRightTopDefend ());    // PT_DEFEND_RIGHT_TOP 右上角的后卫   
        addRole (new RoleRightBotDefend ());    // PF_DEFEND_RIGHT_BOT 右下角的后卫 
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
    // 守门员角色   
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
        // 守门员守门策略   
        //   
        /*  
            A -> B -> C -> .... 优先级最高的为 A  
      
            A. 球在守门员比较近的距离，将球推出保证安全  
                条件：  
                    1. 守门员与球的距离只有半个机器人宽  
                       使劲向非球门方向推球  
      
            B. 不需要防守，守门员退回到球门前的 GOAL_CENTER_X, GOAL_CENTER_Y 位置 - 以垂直的方式移动  
                条件：  
                    1. 球未在 1, 6, 7, 11, 12, 16 区域内  
                    2. 球的速度小于等于 BS_LOW 中低速  
                    3. 球的速度大于等于 BS_MIDDLE_LOW 中高速  
                    4. 球的控制权在敌方处  
                    5. 球的方向为我方球门方向  
      
                    1 & (2 || (3 & 4 & 5))  
      
           C. 需要防守，守门员的 x 轴保持在球门前的 GOAL_CENTER_X  
              1. 如果球在 3, 8, 13, 18, 向我方方向运动，则以球的上次位置，现在位置，算出守门员 Y 轴上对应的点  
                 机器人移动到此点  
                
              2. 机器人的 Y 轴跟着球的 Y 轴移动，并且不超出球门的上下 Y 值  
      
              Y 轴跟着球的 Y 轴移动，并且不超出球门的上下 Y 值  
              如果球在 1, 16 区域则守门员站在对应的两个球门角上  
                条件：  
                    1. A, B, 条件都不满足时  
         */   
        //   
        // 策略 A   
        //   ??
		if (robot.GetDistanceTo(VecPosition(env->predictedBall.pos.x,env->predictedBall.pos.y)) <= (ROBOT_INFO::HALF_DIAGNOL+BALL_INFO::RADIUS)) {   
            //   
            // 将球踢出会不精确，造成守门员跑开岗位 - 先分析一下其它队的策略   
            //   
       
            ////   
            //// 救球   
            ////   
            if (canShoot (robot.pos.x, robot.pos.y, env->currentBall.pos.x, env->currentBall.pos.y) == true) {   
              actShoot (robot, *env);   
              return;   
            }   
        }   
       
        //   
        // 策略 B   
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
            // 允许守门员站立的位置有半个机器人的偏差   
            //   
            double x = GOAL_CENTER_X;   
            double y = GOAL_CENTER_Y;   
           
            ////   
            //// 如果守门员当前在 点 (X, Y) 的 1/4 个机器人的范围内则不需要移动   
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
            //  // 将机器人面向对方球门的角度   
            //  // TODO:actTrun 方法不精确，有问题   
            //  //   
            //  return;   
            //}   
       
            //   
            // 移动到中点位置 - 以垂直的方式移动   
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
        // 策略 C   
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
       
        // 移动到的 Y 坐标超出球门的 Y 坐标时将 Y 坐标改为球门的 Y 坐标   
        //   
        if (targetY > GTOPY - ROBOT_DIAMETER / 2)   
            targetY = GTOPY - ROBOT_DIAMETER / 2;   
        if (targetY < GBOTY + ROBOT_DIAMETER / 2)   
            targetY = GBOTY + ROBOT_DIAMETER / 2;   
       
        actToPosition (robot, targetX, targetY);   
    }   
       
    //   
    // 从还未分配的机器人中找出离指定点最近的机器人   
    //   
    #define FIND_ROBOT(pointX, pointY)    return helpAssignRobots(robots,robotIndexs,lastRole,pointX,pointY);
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // 上前锋角色   
    //   
    // 负责 3, 4, 5, 8, 9, 10 区域，在此区域内将球向敌方球场方向踢   
    // 尽量将球踢给中间的助攻队员   
    //   
       
    // public   
    long   
    RoleVanguardTop::assignRobots (const Robot *robots,   
                                   const vector <long> &robotIndexs,   
                                   const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为进攻队形的上前锋角色   
        // 因此选择一个在离 球场右上角 最近的机器人但任此角色   
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
            上前锋角色进攻  
            负责区域为 3, 4, 5, 8, 9, 10  
                1. 当球在其它区域时以球的 X 轴移动, Y 轴为上半场的中间位置  
                2. 球一旦进入所负责的区域则执行踢球任务 不执行射门任务  
                   射门由助功角色完成  
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
        // 跟着球的 X 轴移动, Y 轴为上半场的中间位置   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y + FIELD_HEIGHT / 4;   
    
       
        x = env->predictedBall.pos.x;   
       
        //   
        // 如果 X 超过对方小禁区 X 轴，则停留在 对方小禁区 X 轴上   
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
    // 下前锋角色   
    //   
       
    // public   
    long   
    RoleVanguardBottom::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为进攻队形的上前锋角色   
        // 因此选择一个在离 球场右上角 最近的机器人但任此角色   
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
            下前锋角色进攻  
            负责区域为 13, 14, 15, 18, 19, 20  
                1. 当球在其它区域时以球的 X 轴移动, Y 轴为上半场的中间位置  
                2. 球一旦进入所负责的区域则执行踢球任务 不执行射门任务  
                   射门由助功角色完成  
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
        // 跟着球的 X 轴移动, Y 轴为下半场的中间位置   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y - FIELD_HEIGHT / 4;   
       
        x = env->predictedBall.pos.x;   
       
        //   
        // 如果 X 超过对方小禁区 X 轴，则停留在 对方小禁区 X 轴上   
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
    // 进攻队形的助功角色   
    //   
       
    // public   
    long   
    RoleAttack::assignRobots (const Robot *robots,   
                              const vector <long> &robotIndexs,   
                              const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为进攻队形的助攻角色   
        // 因此选择一个在离 敌方球门 最近的机器人但任此角色   
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
            助攻角色  
            负责区域 敌方小禁区高度 对应的区域  
                1. 当球在其它区域时以球的 X 轴移动, Y 轴为球场的中间位置  
                2. 球一旦进入所负责的区域则执行射门任务  
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
        // 跟着球的 X 轴移动, Y 轴为上半场的中间位置   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y;
        x = env->predictedBall.pos.x;   
       
        //   
        // 如果 X 超过对方小禁区 X 轴，则停留在 对方小禁区 X 轴上   
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
    // 进攻护卫角色   
    //   
       
    // public    
    long   
    RoleAttackDefend::assignRobots (const Robot *robots,   
                                    const vector <long> &robotIndexs,   
                                    const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为进攻队形的护卫角色   
        // 因此选择一个在离 我方球门 最近的机器人但任此角色   
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
            进攻护卫角色  
            负责区域为 1, 2, 3, 6, 7, 8, 11, 12, 13, 16, 17, 18  
                1. 当球在其它区域时以球的 Y 轴移动, X 轴为我方半场的中间位置  
                2. 球一旦进入所负责的区域则执行踢球任务 不执行射门任务  
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
        // 跟着球的 X 轴移动, Y 轴为上半场的中间位置   
        //   
        double x = 0,   
               y = FIELD_CENTER_Y;
        x = env->predictedBall.pos.x;   
       
        //   
        // 如果 X 超出我方半场的中线 X 轴则 X ＝ 我方半场的中线 X   
        //   
        double defendX = FLEFTX + FIELD_WIDTH / 4;      // 进攻后卫的默认 X   
       
        if (x > defendX ) {   
            double tempY = 0;  
            x = defendX;   
        }   
       
        actToPosition (robot, x, y);   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    //防守型角色 - 左上角的后卫   
    //   
    // public   
    long   
    RoleLeftTopDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为防守队形的左上角的后卫角色   
        // 因此选择一个在离 球场左上角 最近的机器人但任此角色   
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
    //防守型角色 - 左下角的后卫   
    //   
    // public   
    long   
    RoleLeftBotDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为防守队形的左上角的后卫角色   
        // 因此选择一个在离 球场左上角 最近的机器人但任此角色   
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
    //防守型角色 - 右上角的后卫   
    //   
    // public   
    long   
    RoleRightTopDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为防守队形的右上角的后卫角色   
        // 因此选择一个在离 球场右上角 最近的机器人但任此角色   
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
        // 球在 2, 7 区域内时如果不可以踢球则机器人一直保持在 禁区线上的连线位置   
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
    //防守型角色 - 右下角的后卫   
    //   
    // public   
    long   
    RoleRightBotDefend::assignRobots (const Robot *robots,   
                                      const vector <long> &robotIndexs,   
                                      const LastRole &lastRole,const Environment *env)   
    {   
        //   
        // 因当前角色为防守队形的右下角的后卫角色   
        // 因此选择一个在离 球场右下角 最近的机器人但任此角色   
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
        // 球在 12, 17 区域内时如果不可以踢球则机器人一直保持在 禁区线上的连线位置   
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