#include "stdafx.h"
#include "MyStrategy.h"
#include "objects.h"
#include "base.h"
#include "area.h"
#include "teamorder.h"
#include "robotrole.h"
#include "BallFieldAnalyse.h"
#include "BasicScriptServer.h"
#define OUTPUT_FILE "C:\\out.txt"
#define INPUT_FILE "C:\\in.txt"
BasicScriptServer scriptServer(INPUT_FILE,OUTPUT_FILE);
//

void Strategy::PreProcess(){
	StrategyBasis::PreProcess();
	//
	scriptServer.close();
	//
	scriptServer.check();
	scriptServer.startOutPut();
}
void Strategy::PostProcess(){
	scriptServer.endOutPut();
	//
	StrategyBasis::PostProcess();
}

void Strategy::DecisionMaking() {
	static int mode=0;
	static int args[10];
	static int ids[10];
	static VecPosition targets[10];
	static double angles[10];
	static int p=0;
#define target targets[p]
#define angle angles[p]
#define id ids[p]
	//
	while(!scriptServer.isEmpty()){
		string script=scriptServer.getScript();
		if(sscanf(script.c_str(),"setMode(%d)",args+0)==1){
			mode=args[0];
			scriptServer.getOut()<<"set mode:"<<mode<<endl;
		}else if(sscanf(script.c_str(),"moveRobot(%d,%d,%d)",args+0,args+1,args+2)==3){
			p=0;
			id=args[0];
			target.SetX(args[1]);target.SetY(args[2]);
			scriptServer.getOut()<<"Moving robot("<<id<<")"<<endl;
		}else if(sscanf(script.c_str(),"moveAngle(%d,%d)",args+0,args+1)==2){
			p=1;
			angle=args[0];
			target.SetX(args[1]);target.SetY(args[2]);
			scriptServer.getOut()<<"Moving robot("<<id<<")"<<endl;
		}else if(strcmp(script.c_str(),"cm")==0){
			mode=(++mode)%2;
		}else {//cant' recognize
			scriptServer.getOut()<<script<<endl;
		}
	}
	
	//
	static BallFieldState _ballFieldState;
	

	static MyEnvironment myenv;
	static MyEnvironment *env=&myenv;
	static RoleManager _roleMgr;
	static LastRole _lastRole;
	myenv.update(this);
	if(this->get_gs().matchState!=MatchState::MS_UNDER_WAY){
		//init the condition:
		_lastRole.init();
	}
	//
	_ballFieldState.analyse (*env);         // 分析球场状�?   
        _ballFieldState.predictBall(*env);     // 预估小球的位�?   
      // cout<<"\nBall is in the ";_ballFieldState.getBallArea()->print();cout<<endl;
 
        //   
	   static TeamManager _teamMgr;
	  // TeamOrder *team = _teamMgr.getTeam(2);//attackTeamOrder
	 
        TeamOrder *team = _teamMgr.getTeam (_ballFieldState.getBallArea (),   
                                            _ballFieldState.getBallSpped (),   
                                            _ballFieldState.getBallDirection (),   
                                            _ballFieldState.getBallPower (),   
                                            _ballFieldState.getGuardLeak ());/**/
		//cout<<"Choose team: "<<team->getName()<<endl;
		//cout<<"Ball is in ";_ballFieldState.getBallArea()->print();cout<<" pos:("<<this->get_ball().get_position().GetX()<<","<<this->get_ball().get_position().GetY()<<")"<<endl;
        if (team == 0) {   
            //ASSERT (false);   
            return;   
        }   
		//team->print();
        RoleType *roleTypes = team->getRoles ();   
		if (roleTypes == 0) {   
            //ASSERT (false);   
            return;   
        }
        //   
 
        //   
        vector <long> robotIndexs;     
        for (int i = 0; i < PLAYERS_PER_SIDE; ++i){
            robotIndexs.push_back (i); 
		}
        RoleType roles[PLAYERS_PER_SIDE];   
   
		
		//cout<<"Assign:"<<endl;
        for (int i = 0; i < PLAYERS_PER_SIDE; ++i) {   
             RobotRole *role = _roleMgr.getRole (roleTypes[i]);   
            long  index= role->assignRobots (env->home, robotIndexs,_lastRole,env);   
			// cout<<index<<":"<<convertRoleType(roleTypes[i])<<endl;
          
				role->strategy (env->home[index],   
                            _ballFieldState.getBallArea (),   
                            _ballFieldState.getBallSpped (),   
                            _ballFieldState.getBallDirection (),   
                            _ballFieldState.getBallPower (),   
                            _ballFieldState.getGuardLeak (),   
                            env);   
			
      
            roles[index] = roleTypes[i];   
       
     
            typedef vector <long>::iterator iterator;   
            iterator itend = robotIndexs.end ();   
			iterator it;
			for (it = robotIndexs.begin (); it != itend; ++it) {   
                if (*it == index) {   
                    robotIndexs.erase (it);   
                    break;   
                }   
            }  /**/  
             //if (it == itend)   
            //  ASSERT (false);   
        }   
		
        for (int i = 0; i < PLAYERS_PER_SIDE; ++i)   
            _lastRole.role[i] = roles[i];   
		//
	
		//
		//
	if(mode==0){//normal,run the strategy
		for(int i=0;i<PLAYERS_PER_SIDE;i++){
			env->home[i].copyToRobot();
			this->robots_[i].set_left_velocity(env->home[i].velocityLeft);
			this->robots_[i].set_right_velocity(env->home[i].velocityRight);
		}
	}else if(mode==1){
		p=0;
		id=1;
		target=VecPosition(110,90);
		robots_[id].ToPositionPD(target,ROBOT_INFO::WHEEL::MAX_SPEED);
		p=1;
		robots_[id].TurnToAngle(angle);
	}
	//robots_[2].ToPositionPD(ballPos+vec_dir+forward,maxSpeed);
	//robots_[3].ToPositionPD(ballPos-vec_dir+forward,maxSpeed);
	// TODO: Add strategy detail here.


}/*   */