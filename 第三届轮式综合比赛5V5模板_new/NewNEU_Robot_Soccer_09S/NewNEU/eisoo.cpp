    /****************************************************************************************************  
    eisoo.cpp 艾数机器人足球策略源文件  
      
    Purpose:  
        策略头文�?,包括区域管理，状态分�?  
      
    author:  
        yy_cn  
      
    Created Time:  
        2006-5-8  
    ****************************************************************************************************/   
       
    #include "eisoo.h"   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // 球场上的状态信�?   
    //   
       
    // public   
    BallFieldState::BallFieldState (void)   
        : _ballArea (0)                 // 球所在的区域   
        , _ballSpeed (BS_UNKNOWN)       // 球的速度   
        , _ballDirection (BD_UNKNOWN)   // 球的运动方向   
        , _ballPower (BP_UNKNOWN)       // 球的控制�?   
        , _guardLeak (GL_UNKNOWN)       // 防守漏洞情况   
        , _areaMgr ()                   // 管理区域信息   
    {   
    }   
       
    // public   
    BallFieldState::~BallFieldState (void)   
    {      
    }   
       
    // public   
    void   
    BallFieldState::analyse (const Environment &env)   
    {   
        //   
        // 分析球所在的区域   
        //   
        analyseBallArea (env.currentBall.pos.x, env.currentBall.pos.y);   
           
        //   
        // 分析球的速度   
        //     
        analyseBallSpeed (env.currentBall.pos.x, env.currentBall.pos.y, env.lastBall.pos.x, env.lastBall.pos.y);   
           
        //   
        // 分析球的运动方向   
        //   
        analyseBallDirection (env.currentBall.pos.x, env.currentBall.pos.y, env.lastBall.pos.x, env.lastBall.pos.y);   
           
        //   
        // 分析球的控件�?   
        //   
        analyseBallPower (env);   
       
        //   
        // 分析防守漏洞情况   
        //   
        analyseGuardLeak (env);   
    }   
       
    // protected   
    void   
    BallFieldState::predictBall (Environment &env)   
    {   
        //   
        // 预测球的下次移动位置   
        //   
        double dx = env.currentBall.pos.x - env.lastBall.pos.x;   
        double dy = env.currentBall.pos.y - env.lastBall.pos.y;   
           
        env.predictedBall.pos.x = env.currentBall.pos.x + dx;   
        env.predictedBall.pos.y = env.currentBall.pos.y + dy;   
    }   
       
    // protected   
    void   
    BallFieldState::analyseBallArea (double x, double y)   
    {   
        //   
        // 分析球所在的区域   
        //   
        transform (x, y);   
        _ballArea = const_cast<AreaInfo*> (_areaMgr.getArea (x, y));   
    }   
       
    // protected   
    void   
    BallFieldState::analyseBallSpeed (double curX, double curY, double lastX, double lastY)   
    {   
        //   
        // 分析球的速度   
        //   
        double distance = getDistance (curX, curY, lastX, lastY);   
       
        _ballSpeed = BS_LOW;   
           
        if (distance = BALL_DIAMETER / 8) {   
            //   
            // 小于球的直径则为低�?   
            //   
            _ballSpeed = BS_LOW;   
        }   
        else if (distance > BALL_DIAMETER / 8 && distance = BALL_DIAMETER / 4) {   
            _ballSpeed = BS_MIDDLE_LOW;   
        }   
        else if (distance > BALL_DIAMETER / 4 && distance = BALL_DIAMETER / 2) {   
            _ballSpeed = BS_MIDDLE;   
        }   
        else if (distance > BALL_DIAMETER / 2 && distance = BALL_DIAMETER) {   
            _ballSpeed = BS_HIGH;   
        }   
        else if (distance > BALL_DIAMETER) {   
            _ballSpeed = BS_MORE_HIGH;   
        }   
    }   
       
    // protected   
    void   
    BallFieldState::analyseBallDirection (double curX, double curY, double lastX, double lastY)   
    {   
        //   
        // 分析球的运动方向   
        //   
        transform (curX, curY);   
        transform (lastX, lastY);      
           
        if (curX == lastX && curY  == lastY) {   
            _ballDirection = BD_REST;           // 静止   
        }   
        else if (curX == lastX && curY > lastY) {   
            _ballDirection = BD_TOP;            // �?   
        }   
        else if (curX == lastX && curY  lastY) {   
            _ballDirection = BD_BOTTOM;         // �?   
        }   
        else if (curX > lastX && curY == lastY) {   
            _ballDirection = BD_RIGHT;          // �?   
        }   
        else if (curX  lastX && curY == lastY) {   
            _ballDirection = BD_LEFT;           // �?   
        }   
        else if (curX > lastX && curY > lastY) {   
            _ballDirection = BD_RIGHT_TOP;      // 右上   
        }   
        else if (curX > lastX && curY  lastY) {   
            _ballDirection = BD_RIGHT_BOTTOM;   // 右下   
        }   
        else if (curX  lastX && curY  lastY) {   
            _ballDirection = BD_LEFT_TOP;       // 左上   
        }   
        else if (curX  lastX && curY > lastY) {   
            _ballDirection = BD_LEFT_BOTTOM;    // 左下     
        }   
    }   
       
    // protected   
    void  BallFieldState::analyseBallPower (const Environment &env)   
    {   
        //   
        // 分析球的控件�?   
        //   
        double curBallX = env.currentBall.pos.x;   
        double curBallY = env.currentBall.pos.y;   
       
        //   
        // 判断当前离球最近的队员是我方还是敌�?   
        //   
        long myRobot = 0;                               // 记录我方离球最近的对员   
        double myDistance = 0;                          // 最短距�?   
        getVicinityPoint <Robot> ((Robot *) &env.home, curBallX, curBallY, myRobot, myDistance);   
       
        long opponentRobot = 0;                         // 记录敌方离球最近的对员   
        double opponentDistance = 0;                    // 最短距�?   
        getVicinityPoint <OpponentRobot> ((OpponentRobot *) &env.opponent,   
                                          curBallX,   
                                          curBallY,   
                                          opponentRobot,   
                                          opponentDistance);   
       
        double controlDistance = BALL_DIAMETER / 2;   
        if (myDistance  controlDistance && opponentDistance > controlDistance) {   
            _ballPower = BP_SELF;                       // 我方控球   
        }   
        else if (myDistance > controlDistance && opponentDistance  controlDistance) {   
            _ballPower = BP_OPPONENT;                   // 敌方控球   
        }   
        else if (myDistance = controlDistance && opponentDistance = controlDistance) {   
            _ballPower = BP_CONFRONT;                   // 双方顶牛，对�?   
        }   
        else {   
            _ballPower = BP_WITHOUT;                    // 双方皆不控球   
        }      
    }   
       
    // protected   
    void   
    BallFieldState::analyseGuardLeak (const Environment &env)   
    {   
        //   
        // 分析防守漏洞情况   
        //   
        _guardLeak = GL_OPPONENT_MORE_BIG;   
    }   
       
    ////////////////////////////////////////////////////////////////////////////////////////////////////   
    //   
    // 决策系统   
    //   
       
    // public   
    DecisionSystem::DecisionSystem (void)   
        : _ballFieldState ()   
        , _teamMgr ()   
        , _roleMgr ()   
        , _lastRole ()   
    {   
    }   
       
    // public   
    DecisionSystem::~DecisionSystem (void)   
    {   
    }   
       
    // public   
    void   
    DecisionSystem::strategy (Environment *env)   
    {   
        _ballFieldState.analyse (*env);         // 分析球场状�?   
        _ballFieldState.predictBall (*env);     // 预估小球的位�?   
       
        //   
        // 跟据状态获得队�?   
        //   
        TeamOrder *team = _teamMgr.getTeam (_ballFieldState.getBallArea (),   
                                            _ballFieldState.getBallSpped (),   
                                            _ballFieldState.getBallDirection (),   
                                            _ballFieldState.getBallPower (),   
                                            _ballFieldState.getGuardLeak ());   
           
        if (team == 0) {   
            //ASSERT (false);   
            return;   
        }   
       
        RoleType *roleTypes = team->getRoles ();   
        if (roleTypes == 0) {   
            //ASSERT (false);   
            return;   
        }   
       
        //   
        // 从角色管理中获得具体的角�?   
        //   
        vector <long> robotIndexs;            // 未分配角色的机器�?   
        for (int i = 0; i < PLAYERS_PER_SIDE; ++i)   
            robotIndexs.push_back (i);   
       
        //   
        // 保存角色对应的机器人   
        // 索引值对应的为机器人索引�?   
        // �? role[0] == RT_UNKNOWN 则为 机器�? 0 上一次分配的角色为未知角�?   
        //   
        RoleType roles[PLAYERS_PER_SIDE];   
       
        //   
        // 为角色起分配机器�?   
        //   
        for ( i = 0; i < PLAYERS_PER_SIDE; ++i) {   
            RobotRole *role = _roleMgr.getRole (roleTypes[i]);   
       
            //   
            // 获得最合适的机器人索引�?   
            //   
            long index = role->assignRobots (env->home, robotIndexs, _lastRole);   
       
            //   
            // 执行此角色的策略   
            //   
            role->strategy (env->home[index],   
                            _ballFieldState.getBallArea (),   
                            _ballFieldState.getBallSpped (),   
                            _ballFieldState.getBallDirection (),   
                            _ballFieldState.getBallPower (),   
                            _ballFieldState.getGuardLeak (),   
                            env);   
       
            //   
            // 保存角色对应的机器人   
            // 机器�? index 分配的角色为当前 roleTypes[i]   
            //   
            roles[index] = roleTypes[i];   
       
            //   
            // 从未分配角色的机器人中抹去这个已分配的机器人   
            //   
            typedef vector <long>::iterator iterator;   
            iterator itend = robotIndexs.end ();   
            for (iterator it = robotIndexs.begin (); it != itend; ++it) {   
                if (*it == index) {   
                    robotIndexs.erase (it);   
                    break;   
                }   
            }   
            //if (it == itend)   
            //  ASSERT (false);   
        }   
       
        //   
        // 角色策略都已经执行完�?   
        //   
        // 记录这一次分配的机器人角�?   
        //   
        for ( i = 0; i  PLAYERS_PER_SIDE; ++i)   
            _lastRole.role[i] = roles[i];   
    }   
       
       


