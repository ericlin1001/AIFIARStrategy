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
class Enviornment_Info;
class AreaInfo; 
class RobotRole; 
 
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
	virtual long assignRobots (const RobotPID *robots, 
							   const vector <long> &robotIndexs, 
							   const LastRole &lastRole) = 0; 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	virtual void strategy (RobotPID &robot, 
						   const AreaInfo *areaInfo, 
						   BallSpeed speed, 
						   BallDirection direction, 
						   BallPower power, 
						   GuardLeak leak, 
						   Enviornment_Info *env) = 0; 
 
protected: 
	RoleType _type;			// ��ɫ���� 
}; // end class RobotRole 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
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
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak,
				   Enviornment_Info *env); 
}; // end class RoleGoalkeeper 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
// 
// ��ǰ���ɫ 
// 
class RoleVanguardTop : public RobotRole 
{ 
public: 
	RoleVanguardTop (void) 
		: RobotRole (RT_VANGUARD_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleVanguardTop 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
// 
// ��ǰ���ɫ 
// 
class RoleVanguardBottom : public RobotRole 
{ 
public: 
	RoleVanguardBottom (void) 
		: RobotRole (RT_VANGUARD_BOTTOM) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class Vanguard 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
// 
// �������ε�������ɫ 
// 
class RoleAttack : public RobotRole 
{ 
public: 
	RoleAttack (void) 
		: RobotRole (RT_ATTACK) 
	{ 
	}; 
 
	~RoleAttack (void) {}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleAttack 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
// 
// ����������ɫ 
// 
class RoleAttackDefend : public RobotRole 
{ 
public: 
	RoleAttackDefend (void) 
		: RobotRole (RT_ATTACK_DEFEND) 
	{ 
	}; 
 
	~RoleAttackDefend (void) {}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleAttackDefend 
 
//////////////////////////////////////////////////////////////////////////////////////
////////////// 
// 
// �����ͽ�ɫ - ���Ͻǵĺ��� 
// 
class RoleLeftTopDefend : public RobotRole 
{ 
public: 
	RoleLeftTopDefend (void) 
		: RobotRole (RT_DEFEND_LEFT_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleLeftTopDefend 
 
 
// 
// �����ͽ�ɫ - ���½ǵĺ��� 
// 
class RoleLeftBotDefend : public RobotRole 
{ 
public: 
	RoleLeftBotDefend (void) 
		: RobotRole (RT_DEFEND_LEFT_BOT) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleLeftBotDefend 
 
// 
// �����ͽ�ɫ - ���Ͻǵĺ��� 
// 
class RoleRightTopDefend : public RobotRole 
{ 
public: 
	RoleRightTopDefend (void) 
		: RobotRole (RT_DEFEND_RIGHT_TOP) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleRightTopDefend 
 
// 
// �����ͽ�ɫ - ���½ǵĺ��� 
// 
class RoleRightBotDefend : public RobotRole 
{ 
public: 
	RoleRightBotDefend (void) 
		: RobotRole (RT_DEFEND_RIGHT_BOT) 
	{ 
	}; 
 
	/** 
	 * ��������� 
	 */ 
	long assignRobots (const RobotPID *robots, 
					   const vector <long> &robotIndexs, 
					   const LastRole &lastRole); 
 
	/** 
	 * ��ɫִ����Ӧ�Ĳ��� 
	 */ 
	void strategy (RobotPID &robot, 
				   const AreaInfo *areaInfo, 
				   BallSpeed speed, 
				   BallDirection direction, 
				   BallPower power, 
				   GuardLeak leak, 
				  Enviornment_Info *env); 
}; // end class RoleRightBotDefend 
 
#endif // end __ROBOT_ROLE_H__ 


