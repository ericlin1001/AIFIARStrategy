/**************************************************************************************************** 
robotrole.h 艾数机器人角色头文件 
 
Purpose: 
	角色可以使用的动作 
 
author: 
	yy_cn 
 
Created Time: 
	2006-5-9 
****************************************************************************************************/ 
 
#ifndef __ROBOT_ROLE_H__ 
#define __ROBOT_ROLE_H__ 
 
#include "base.h" 
#include "strategy.h"
class AreaInfo; 
class RobotRole; 
#define Environment MyEnvironment  
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 角色管理 
// 
class RoleManager 
{ 
public: 
	RoleManager (void); 
	~RoleManager (void); 
 
	/** 
	 * 添加角色 
	 */ 
	void addRole (RobotRole *role); 
 
	/** 
	 * 跟据角色类型获得角色对象 
	 */ 
	RobotRole *getRole (RoleType type); 
 
public: 
	// 
	// 所有角色 
	// 
	vector <RobotRole *> _roles;			// 添加顺序与 RoleType 顺序一至 
											// 查到对应的角色时可以使用 _roles[RT_GOALKEEPER] 的方式 
}; // end RoleManager 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 机器人角色 
// 
class RobotRole 
{ 
public: 
	RobotRole (RoleType type) 
		: _type (type) 
	{ 
	}; 
 
	~RobotRole (void) {}; 
 
	/** 
	 * 获得角色的类型 
	 */ 
	RoleType getType (void) const 
	{ 
		return _type; 
	}; 
 
	/** 
	 * 跟据机器人的信息和上一次的分配情况来分配角色 
	 * 优先考虑同一个机器人分配与上一次分配相同的角色 
	 * @param robotIndexs 未分配角色的机器人，从这些机器人中找出最合适的 
	 * @param lastRole 上一次分配的角色与对应的机器人 
	 */ 
	virtual long helpAssignRobots(const Robot *robots, 
							   const vector <long> &robotIndexs, 
							   const LastRole &lastRole,double pointX,double pointY){
								   
								    long index = robotIndexs[0];    
								    double distance = 9999;     /* 保存上次选择的最短距离机器人的距离 */   
                                                                                      
            double goalX = pointX;      /* 球场的右边界   */                            
            double goalY = pointY;      /* 场地上边界 */                           
 

            /**/                                                                      
            /* 从未分配的机器中找出最合适的机器人 */                               
            /**/                                                                      
            typedef vector <long>::const_iterator iterator;                             
            iterator itend = robotIndexs.end ();                                      
            for (iterator it = robotIndexs.begin (); it != itend; ++it) {             
                if (lastRole.role[(*it)] == getType ()) {                             
                    /**/                                                              
                    /* 上一次分配的角色中包含当前需要分配的角色 */                    
                    /* 为了保证角色执行任务的连续性，使用同样的机器人来当任此角色 */
                    /**/                                                              
                    index = *it;                                                      
                    break;                                                            
                }                                                                     
                                                                                      
                /**/                                                                  
                /* 获得当前机器人与球场右上角的距离 */                                
                /**/                                                                  
                double tempDe = getDistance (robots[(*it)].pos.x, robots[(*it)].pos.y, goalX, goalY);   
                if (tempDe<distance) {                                           
                    index = *it;                                                      
                    distance = tempDe;                                                
                }                                                                     
            }                                                                         
                                                                                     
            return index;                                                             
        
	}
	virtual long assignRobots (const Robot *robots, 
							   const vector <long> &robotIndexs, 
							   const LastRole &lastRole,
							   const Environment *env=NULL)=0;
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	virtual void strategy (Robot &robot, 
						   const AreaInfo *areaInfo, 
						   BallSpeed speed, 
						   BallDirection direction, 
						   BallPower power, 
						   GuardLeak leak, 
						   const Environment *env) = 0; 
 
protected: 
	RoleType _type;			// 角色类型 
}; // end class RobotRole 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 守门员角色 
// 
class RoleGoalkeeper : public RobotRole 
{ 
public: 
	RoleGoalkeeper (void) 
		: RobotRole (RT_GOALKEEPER) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
							   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleGoalkeeper 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 上前锋角色 
// 
class RoleVanguardTop : public RobotRole 
{ 
public: 
	RoleVanguardTop (void) 
		: RobotRole (PT_VANGUARD_TOP) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleVanguardTop 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 下前锋角色 
// 
class RoleVanguardBottom : public RobotRole 
{ 
public: 
	RoleVanguardBottom (void) 
		: RobotRole (PT_VANGUARD_BOTTOM) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class Vanguard 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 进攻队形的助功角色 
// 
class RoleAttack : public RobotRole 
{ 
public: 
	RoleAttack (void) 
		: RobotRole (PT_ATTACK) 
	{ 
	}; 
 
	~RoleAttack (void) {}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleAttack 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 进攻护卫角色 
// 
class RoleAttackDefend : public RobotRole 
{ 
public: 
	RoleAttackDefend (void) 
		: RobotRole (PT_ATTACK_DEFEND) 
	{ 
	}; 
 
	~RoleAttackDefend (void) {}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleAttackDefend 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 防守型角色 - 左上角的后卫 
// 
class RoleLeftTopDefend : public RobotRole 
{ 
public: 
	RoleLeftTopDefend (void) 
		: RobotRole (PT_DEFEND_LEFT_TOP) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleLeftTopDefend 
 
 
// 
// 防守型角色 - 左下角的后卫 
// 
class RoleLeftBotDefend : public RobotRole 
{ 
public: 
	RoleLeftBotDefend (void) 
		: RobotRole (PT_DEFEND_LEFT_BOT) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleLeftBotDefend 
 
// 
// 防守型角色 - 右上角的后卫 
// 
class RoleRightTopDefend : public RobotRole 
{ 
public: 
	RoleRightTopDefend (void) 
		: RobotRole (PT_DEFEND_RIGHT_TOP) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleRightTopDefend 
 
// 
// 防守型角色 - 右下角的后卫 
// 
class RoleRightBotDefend : public RobotRole 
{ 
public: 
	RoleRightBotDefend (void) 
		: RobotRole (PF_DEFEND_RIGHT_BOT) 
	{ 
	}; 
 
	/** 
	 * 分配机器人 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * 角色执行相应的策略 
	 */ 
	void strategy (Robot &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				   const Environment *env); 
}; // end class RoleRightBotDefend 

//some helpful macro
#define REGISTER_ROLECLASS_MACRO(className,type) class className : public RobotRole{ \
public:className (void):RobotRole (type){}\
	long assignRobots (const Robot *robots,const vector <long> &robotIndexs,const LastRole &lastRole,const Environment *env=NULL); \
	void strategy ( Robot &robot, \
					const AreaInfo *areaInfo, \
					BallSpeed speed, \
					BallDirection direction, \
					BallPower power, \
					GuardLeak leak, \
					const Environment *env); \
}; // end class
#define ASSIGNROBOT_MACRO(className) long className::assignRobots (const Robot *robots,   \
                                   const vector <long> &robotIndexs,   \
                                   const LastRole &lastRole,const Environment *env)
#define STRATEGY_MACRO(className) void className::strategy (Robot &robot,   \
                               const AreaInfo *areaInfo,   \
                               BallSpeed speed,   \
                               BallDirection direction,   \
                               BallPower power,  \
                               GuardLeak leak,  \
                               const Environment *env)  
//end the macro
REGISTER_ROLECLASS_MACRO(RoleTest,RT_TEST);

#endif // end __ROBOT_ROLE_H__ 


