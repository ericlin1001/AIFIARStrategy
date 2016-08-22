/**************************************************************************************************** 
teamorder.h 艾数机器人队形头文件 
 
Purpose: 
	完成特定目的地队形分配，每个队形使用最合适的角色 
 
author: 
	yy_cn 
 
Created Time: 
	2006-5-10 
****************************************************************************************************/ 
 
#ifndef __ROBOT_TEAM_ORDER_H__ 
#define __ROBOT_TEAM_ORDER_H__ 
 
#include "base.h" 


class AreaInfo; 
class TeamOrder; 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 队形管理 
// 
class TeamManager 
{ 
public: 
	TeamManager (void); 
	~TeamManager (void); 
 
	/** 
	 * 添加队形 
	 */ 
	void addTeam (TeamOrder *team); 
 
	/** 
	 * 跟据状态获得队形 
	 */ 
	TeamOrder *getTeam (const AreaInfo *areaInfo, 
						BallSpeed speed, 
						BallDirection direction, 
						BallPower power, 
						GuardLeak leak); 
	TeamOrder *getTeam(int index=0){
		return _teams[index];
	}
protected: 
	// 
	// 队形库 
	// 
	vector <TeamOrder *> _teams; 
}; // end class TeamManager 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 队形 
// 
class TeamOrder 
{ 
public: 
	TeamOrder (TeamNumber number); 
	~TeamOrder (void); 
 virtual const char *getName(){
		return "TeamOrder";
	}
	/** 
	 * 获得队形所安排的角色 
	 */ 
	RoleType *getRoles (void) 
	{ 
		return _roles; 
	}; 
 virtual void print()const{
		for(int i=0;i<PLAYERS_PER_SIDE;i++){
			cout<<i<<":"<<convertRoleType(_roles[i])<<endl;
		}
	}
protected: 
	/** 
	 * 条件是否命中 
	 */ 
	virtual bool isHit (const AreaInfo *areaInfo, 
						BallSpeed speed, 
						BallDirection direction, 
						BallPower power, 
						GuardLeak leak); 
 
	/** 
	 * 不同的队形使用不同的角色 
	 * 初始化分配角色 
	 * 最重要的角色安排在最前面 
	 */ 
	virtual bool initRoles (void) 
	{ 
		return false; 
	}; 
 
	/** 
	 * 初始化使用队形时所需要的状态条件 
	 */ 
	virtual bool initCondition (void) 
	{ 
		return false; 
	}; 
	
protected: 
	// 
	// 最重要的角色排在最前面 0 -> 1 -> 2 -> 3 -> 4 
	// 
	void addRole (RoleType role, int index);			// 添加角色 
 
	void addBallArea (BallArea area);					// 添加符合的区域 
	void addBallSpeed (BallSpeed speed);				// 添加符合的球的速度 
	void addBallDirection (BallDirection direction);	// 添加符合的球的运动方向 
	void addBallPower (BallPower power);				// 添加符合的球控制权 
	void addGuardLeak (GuardLeak leak);					// 添加符合的漏洞情况 
 
	void addAllArea (void);								// 添加所有区域 
	void addAllSpeed (void);							// 添加所有速度 
	void addAllDirection (void);						// 添加所有方向 
	void addAllPower (void);							// 添加所有控制权 
	void addAllGuardLeak (void);						// 添加所有漏洞 
 
protected: 
	// 
	// 队形所需要的角色 
	// 
	RoleType _roles[PLAYERS_PER_SIDE]; 
 
	// 
	// 使用队形时所需要的状态条件 
	// 
	vector <BallArea> _areas; 
	vector <BallSpeed> _speeds; 
	vector <BallDirection> _directions; 
	vector <BallPower> _powers; 
	vector <GuardLeak> _leaks; 
	TeamNumber _number; 
	friend class TeamManager; 
}; // end TeamOrder 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 进攻队形 - TN_ATTACK 
// 
class AttackTeam : public TeamOrder 
{ 
public: 
	AttackTeam (void) 
		: TeamOrder (TN_ATTACK) 
	{ 
	}; 
 virtual const char *getName(){
		return "AttackTeam";
	}
	/** 
	 * 初始化分配角色 
	 */ 
	virtual bool initRoles (void); 
 
	/** 
	 * 初始化使用队形时所需要的状态条件 
	 */ 
	virtual bool initCondition (void); 
	
}; // end class AttackTeam 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// 防守队形 - TN_DEFEND 
// 
class DefendTeam : public TeamOrder 
{ 
public: 
	DefendTeam (void) 
		: TeamOrder (TN_ATTACK) 
	{ 
	}; 
 virtual const char *getName(){
		return "DefendTeam";
	}
	/** 
	 * 初始化分配角色 
	 */ 
	virtual bool initRoles (void); 
 
	/** 
	 * 初始化使用队形时所需要的状态条件 
	 */ 
	virtual bool initCondition (void); 
}; // end class DefendTeam 
//some helpful macro 
#define REGISTER_TEAM_MACRO(className,type) class className : public TeamOrder{ \
public: \
	className (void):TeamOrder (type) {}; \
 virtual const char *getName(){return #className;}\
	virtual bool initRoles (void);\
	virtual bool initCondition (void); \
}; // end class
#define INITROLES_MACRO(className) bool  className::initRoles (void) 
#define INITCONDITION_MACRO(className) bool className::initCondition (void)   
//end macro  
REGISTER_TEAM_MACRO(TestTeam,TT_TEST);
#endif // __ROBOT_TEAM_ORDER_H__


