/**************************************************************************************************** 
teamorder.h ���������˶���ͷ�ļ� 
 
Purpose: 
	����ض�Ŀ�ĵض��η��䣬ÿ������ʹ������ʵĽ�ɫ 
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
	 * ���Ӷ��� 
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
	vector <TeamOrder *> teams; 
}; // end class TeamManager 
 
//////////////////////////////////////////////////////////////////////////////////////////////////// 
// 
// ���� 
// 
class TeamOrder 
{ 
public: 
	TeamOrder (TeamType type); 
	~TeamOrder (void); 
 
	/** 
	 * ��ö��������ŵĽ�ɫ 
	 */ 
	RoleType *getRoles (void) {return roles;}; 
	virtual char *getName(){return "TeamOrder";}
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
	void addRole (RoleType role, int index);			// ���ӽ�ɫ 
 
	void addBallArea (BallArea area);					// ���ӷ��ϵ����� 
	void addBallSpeed (BallSpeed speed);				// ���ӷ��ϵ�����ٶ� 
	void addBallDirection (BallDirection direction);	// ���ӷ��ϵ�����˶����� 
	void addBallPower (BallPower power);				// ���ӷ��ϵ������Ȩ 
	void addGuardLeak (GuardLeak leak);					// ���ӷ��ϵ�©����� 
 
	void addAllArea (void);								// ������������ 
	void addAllSpeed (void);							// ���������ٶ� 
	void addAllDirection (void);						// �������з��� 
	void addAllPower (void);							// �������п���Ȩ 
	void addAllGuardLeak (void);						// ��������©�� 
 
protected: 
	// 
	// ��������Ҫ�Ľ�ɫ 
	// 
	RoleType roles[PLAYERS_PER_SIDE]; 
 
	// 
	// ʹ�ö���ʱ����Ҫ��״̬���� 
	// 
	vector <BallArea> areas; 
	vector <BallSpeed> speeds; 
	vector <BallDirection> directions; 
	vector <BallPower> powers; 
	vector <GuardLeak> leaks; 
 
	TeamType teamType; 
 
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
		: TeamOrder (TT_ATTACK) 
	{ 
		Show("AttackTeam constructor");
		Show("end AttackTeam constructor");
	}; 
	/** 
	 * ��ʼ�������ɫ 
	 */ 
	virtual bool initRoles (void); 
	virtual char *getName(){return "AttackTeam";}
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
		: TeamOrder (TT_ATTACK) 
	{ 
		Show("DefendTeam constructor");
		Show("end DefendTeam constructor");
	}; 
 
	/** 
	 * ��ʼ�������ɫ 
	 */ 
	virtual bool initRoles (void); 
	virtual char *getName(){return "DefendTeam";}
	/** 
	 * ��ʼ��ʹ�ö���ʱ����Ҫ��״̬���� 
	 */ 
	virtual bool initCondition (void); 
}; // end class DefendTeam 
 
#endif // __ROBOT_TEAM_ORDER_H__

