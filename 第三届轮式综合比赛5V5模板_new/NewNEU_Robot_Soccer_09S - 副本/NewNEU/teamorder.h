/**************************************************************************************************** 
teamorder.h ���������˶���ͷ�ļ� 
 
Purpose: 
	����ض�Ŀ�ĵض��η��䣬ÿ������ʹ������ʵĽ�ɫ 
 
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
// ���ι��� 
// 
class TeamManager 
{ 
public: 
	TeamManager (void); 
	~TeamManager (void); 
 
	/** 
	 * ��Ӷ��� 
	 */ 
	void addTeam (TeamOrder *team); 
 
	/** 
	 * ����״̬��ö��� 
	 */ 
	TeamOrder *getTeam (const AreaInfo *areaInfo, 
						BallSpeed speed, 
						BallDirection direction, 
						BallPower power, 
						GuardLeak leak); 
 
protected: 
	// 
	// ���ο� 
	// 
	vector <TeamOrder *> _teams; 
}; // end class TeamManager 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ���� 
// 
class TeamOrder 
{ 
public: 
	TeamOrder (TeamNumber number); 
	~TeamOrder (void); 
 
	/** 
	 * ��ö��������ŵĽ�ɫ 
	 */ 
	RoleType *getRoles (void) 
	{ 
		return _roles; 
	}; 
 
protected: 
	/** 
	 * �����Ƿ����� 
	 */ 
	virtual bool isHit (const AreaInfo *areaInfo, 
						BallSpeed speed, 
						BallDirection direction, 
						BallPower power, 
						GuardLeak leak); 
 
	/** 
	 * ��ͬ�Ķ���ʹ�ò�ͬ�Ľ�ɫ 
	 * ��ʼ�������ɫ 
	 * ����Ҫ�Ľ�ɫ��������ǰ�� 
	 */ 
	virtual bool initRoles (void) 
	{ 
		return false; 
	}; 
 
	/** 
	 * ��ʼ��ʹ�ö���ʱ����Ҫ��״̬���� 
	 */ 
	virtual bool initCondition (void) 
	{ 
		return false; 
	}; 
 
protected: 
	// 
	// ����Ҫ�Ľ�ɫ������ǰ�� 0 -> 1 -> 2 -> 3 -> 4 
	// 
	void addRole (RoleType role, int index);			// ��ӽ�ɫ 
 
	void addBallArea (BallArea area);					// ��ӷ��ϵ����� 
	void addBallSpeed (BallSpeed speed);				// ��ӷ��ϵ�����ٶ� 
	void addBallDirection (BallDirection direction);	// ��ӷ��ϵ�����˶����� 
	void addBallPower (BallPower power);				// ��ӷ��ϵ������Ȩ 
	void addGuardLeak (GuardLeak leak);					// ��ӷ��ϵ�©����� 
 
	void addAllArea (void);								// ����������� 
	void addAllSpeed (void);							// ��������ٶ� 
	void addAllDirection (void);						// ������з��� 
	void addAllPower (void);							// ������п���Ȩ 
	void addAllGuardLeak (void);						// �������©�� 
 
protected: 
	// 
	// ��������Ҫ�Ľ�ɫ 
	// 
	RoleType _roles[PLAYERS_PER_SIDE]; 
 
	// 
	// ʹ�ö���ʱ����Ҫ��״̬���� 
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
// �������� - TN_ATTACK 
// 
class AttackTeam : public TeamOrder 
{ 
public: 
	AttackTeam (void) 
		: TeamOrder (TN_ATTACK) 
	{ 
	}; 
 
	/** 
	 * ��ʼ�������ɫ 
	 */ 
	virtual bool initRoles (void); 
 
	/** 
	 * ��ʼ��ʹ�ö���ʱ����Ҫ��״̬���� 
	 */ 
	virtual bool initCondition (void); 
}; // end class AttackTeam 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ���ض��� - TN_DEFEND 
// 
class DefendTeam : public TeamOrder 
{ 
public: 
	DefendTeam (void) 
		: TeamOrder (TN_ATTACK) 
	{ 
	}; 
 
	/** 
	 * ��ʼ�������ɫ 
	 */ 
	virtual bool initRoles (void); 
 
	/** 
	 * ��ʼ��ʹ�ö���ʱ����Ҫ��״̬���� 
	 */ 
	virtual bool initCondition (void); 
}; // end class DefendTeam 
 
#endif // __ROBOT_TEAM_ORDER_H__


