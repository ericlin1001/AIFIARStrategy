/**************************************************************************************************** 
robotrole.h ���������˽�ɫͷ�ļ� 
 
Purpose: 
	��ɫ����ʹ�õĶ��� 
 
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
// ��ɫ���� 
// 
class RoleManager 
{ 
public: 
	RoleManager (void); 
	~RoleManager (void); 
 
	/** 
	 * ��ӽ�ɫ 
	 */ 
	void addRole (RobotRole *role); 
 
	/** 
	 * ���ݽ�ɫ���ͻ�ý�ɫ���� 
	 */ 
	RobotRole *getRole (RoleType type); 
 
public: 
	// 
	// ���н�ɫ 
	// 
	vector <RobotRole *> _roles;			// ���˳���� RoleType ˳��һ�� 
											// �鵽��Ӧ�Ľ�ɫʱ����ʹ�� _roles[RT_GOALKEEPER] �ķ�ʽ 
}; // end RoleManager 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// �����˽�ɫ 
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
	 * ��ý�ɫ������ 
	 */ 
	RoleType getType (void) const 
	{ 
		return _type; 
	}; 
 
	/** 
	 * ���ݻ����˵���Ϣ����һ�εķ�������������ɫ 
	 * ���ȿ���ͬһ�������˷�������һ�η�����ͬ�Ľ�ɫ 
	 * @param robotIndexs δ�����ɫ�Ļ����ˣ�����Щ���������ҳ�����ʵ� 
	 * @param lastRole ��һ�η���Ľ�ɫ���Ӧ�Ļ����� 
	 */ 
	virtual long helpAssignRobots(const Robot *robots, 
							   const vector <long> &robotIndexs, 
							   const LastRole &lastRole,double pointX,double pointY){
								   
								    long index = robotIndexs[0];    
								    double distance = 9999;     /* �����ϴ�ѡ�����̾�������˵ľ��� */   
                                                                                      
            double goalX = pointX;      /* �򳡵��ұ߽�   */                            
            double goalY = pointY;      /* �����ϱ߽� */                           
 

            /**/                                                                      
            /* ��δ����Ļ������ҳ�����ʵĻ����� */                               
            /**/                                                                      
            typedef vector <long>::const_iterator iterator;                             
            iterator itend = robotIndexs.end ();                                      
            for (iterator it = robotIndexs.begin (); it != itend; ++it) {             
                if (lastRole.role[(*it)] == getType ()) {                             
                    /**/                                                              
                    /* ��һ�η���Ľ�ɫ�а�����ǰ��Ҫ����Ľ�ɫ */                    
                    /* Ϊ�˱�֤��ɫִ������������ԣ�ʹ��ͬ���Ļ����������δ˽�ɫ */
                    /**/                                                              
                    index = *it;                                                      
                    break;                                                            
                }                                                                     
                                                                                      
                /**/                                                                  
                /* ��õ�ǰ�������������Ͻǵľ��� */                                
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
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	virtual void strategy (Robot &robot, 
						   const AreaInfo *areaInfo, 
						   BallSpeed speed, 
						   BallDirection direction, 
						   BallPower power, 
						   GuardLeak leak, 
						   const Environment *env) = 0; 
 
protected: 
	RoleType _type;			// ��ɫ���� 
}; // end class RobotRole 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ����Ա��ɫ 
// 
class RoleGoalkeeper : public RobotRole 
{ 
public: 
	RoleGoalkeeper (void) 
		: RobotRole (RT_GOALKEEPER) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
							   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// ��ǰ���ɫ 
// 
class RoleVanguardTop : public RobotRole 
{ 
public: 
	RoleVanguardTop (void) 
		: RobotRole (PT_VANGUARD_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// ��ǰ���ɫ 
// 
class RoleVanguardBottom : public RobotRole 
{ 
public: 
	RoleVanguardBottom (void) 
		: RobotRole (PT_VANGUARD_BOTTOM) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// �������ε�������ɫ 
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
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// ����������ɫ 
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
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// �����ͽ�ɫ - ���Ͻǵĺ��� 
// 
class RoleLeftTopDefend : public RobotRole 
{ 
public: 
	RoleLeftTopDefend (void) 
		: RobotRole (PT_DEFEND_LEFT_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,
					   const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// �����ͽ�ɫ - ���½ǵĺ��� 
// 
class RoleLeftBotDefend : public RobotRole 
{ 
public: 
	RoleLeftBotDefend (void) 
		: RobotRole (PT_DEFEND_LEFT_BOT) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// �����ͽ�ɫ - ���Ͻǵĺ��� 
// 
class RoleRightTopDefend : public RobotRole 
{ 
public: 
	RoleRightTopDefend (void) 
		: RobotRole (PT_DEFEND_RIGHT_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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
// �����ͽ�ɫ - ���½ǵĺ��� 
// 
class RoleRightBotDefend : public RobotRole 
{ 
public: 
	RoleRightBotDefend (void) 
		: RobotRole (PF_DEFEND_RIGHT_BOT) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const Robot *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole,const Environment *env=NULL); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
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


