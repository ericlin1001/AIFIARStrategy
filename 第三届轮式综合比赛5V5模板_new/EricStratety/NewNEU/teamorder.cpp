/****************************************************************************************************  
teamorder.cpp ���������˶���Դ�ļ�  

Purpose:  
����ض�Ŀ�ĵض��η��䣬ÿ������ʹ������ʵĽ�ɫ  


****************************************************************************************************/   

#include "area.h"   
#include "teamorder.h"   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// ���ι���   
//   

// public   
TeamManager::TeamManager (void)   
	: teams ()   
{   
	/********************************************************************************  
	//  
	// ������еĶ���  
	//  
	********************************************************************************/   
	addTeam (new AttackTeam ());   
	addTeam (new DefendTeam ());   
}   

// public   
TeamManager::~TeamManager (void)   
{   
	for_each (teams.begin (), teams.end (), delete_t <TeamOrder> ());   
}   

// public   
void   
	TeamManager::addTeam (TeamOrder *team)   
{   
	if (team == 0) {   
		//ASSERT (false);   
		return;   
	}   
	//   
	// ��ʼ�������ɫ   
	//   
	if (team->initRoles () == false) {   
		//ASSERT (false);   
		;   
	}   

	//   
	// ��ʼ��ʹ�ö���ʱ����Ҫ��״̬����   
	//   
	if (team->initCondition () == false) {   
		//ASSERT (false);   
		;   
	}   
	teams.push_back (team);   
}   

// public   
TeamOrder *   
	TeamManager::getTeam (const AreaInfo *areaInfo,   
	BallSpeed speed,   
	BallDirection direction,   
	BallPower power,   
	GuardLeak leak)   
{   
	typedef vector <TeamOrder *>::const_iterator iterator;   
	iterator itend = teams.end ();   
	for (iterator it = teams.begin (); it != itend; ++it) {   
		if ((*it)->isHit (areaInfo, speed, direction, power, leak) == true)   
			return (*it);   
	}   
	//   
	// û��һ�����η������� .... ��ң�ʹ�û�������   
	//   
	return teams[0];   
}   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// ����   
//   

// public   
TeamOrder::TeamOrder (TeamType type)   
	: teamType (type)   
	, areas ()   
	, speeds ()   
	, directions ()   
	, powers ()   
	, leaks ()   
{   
	for (int i = 0; i < PLAYERS_PER_SIDE; ++i)   
		roles[i] = RT_UNKNOWN; // ��������Ҫ�Ľ�ɫ   
}   

// public   
TeamOrder::~TeamOrder (void)   
{   
}   

// protected   
bool   
	TeamOrder::isHit (const AreaInfo *areaInfo,   
	BallSpeed speed,   
	BallDirection direction,   
	BallPower power,   
	GuardLeak leak)   
{   
	//   
	// ����Ƿ��������   
	// �������״̬������������˵����ǰ���η�������   
	//   
	{   
		//   
		// ������   
		//   
		typedef vector <BallArea>::const_iterator iterator;   
		iterator itend = areas.end (); 
		iterator it ;
		for ( it = areas.begin (); it != itend; ++it) {   
			if ((*it) == areaInfo->getArea ())   
				break;   
		}   
		if (it == itend)   
			return false;   
	}   

	{   
		//   
		// ���ټ��   
		//   
		typedef vector <BallSpeed>::const_iterator iterator;   
		iterator itend = speeds.end ();  
		iterator it;
		for ( it = speeds.begin (); it != itend; ++it) {   
			if (*it == speed)   
				break;   
		}   
		if (it == itend)   
			return false;   
	}   

	{   
		//   
		// ����˶�����   
		//   
		typedef vector <BallDirection>::const_iterator iterator;   
		iterator itend = directions.end (); 
		iterator it;
		for ( it = directions.begin (); it != itend; ++it) {   
			if (*it == direction)   
				break;   
		}   
		if (it == itend)   
			return false;   
	}   

	{   
		//   
		// ��Ŀ���Ȩ   
		//   
		typedef vector <BallPower>::const_iterator iterator;   
		iterator itend = powers.end ();   
		iterator it;
		for ( it = powers.begin (); it != itend; ++it) {   
			if (*it == power)   
				break;;   
		}   
		if (it == itend)   
			return false;   
	}   

	{   
		//   
		// ©��   
		//   
		typedef vector <GuardLeak>::const_iterator iterator;   
		iterator itend = leaks.end ();   
		iterator it;
		for ( it = leaks.begin (); it != itend; ++it) {   
			if (*it == leak)   
				break;   
		}   
		if (it == itend)   
			return false;   
	}   

	//   
	// ��������������   
	//   
	return true;   
}   

// public   
void   
	TeamOrder::addRole (RoleType role, int index)   
{   
	if (index <0 || index >= PLAYERS_PER_SIDE) {   
		//ASSERT (false);   
		return;   
	}   

	roles[index] = role;
}   

// public   
void   
	TeamOrder::addBallArea (BallArea area)   
{   
	areas.push_back (area);   
}   

// public   
void   
	TeamOrder::addBallSpeed (BallSpeed speed)   
{   
	speeds.push_back (speed);   
}   

// public   
void   
	TeamOrder::addBallDirection (BallDirection direction)   
{   
	directions.push_back (direction);   
}   

// public   
void   
	TeamOrder::addBallPower (BallPower power)   
{   
	powers.push_back (power);   
}   

// public   
void   
	TeamOrder::addGuardLeak (GuardLeak leak)   
{   
	leaks.push_back (leak);   
}   

// public   
void   
	TeamOrder::addAllArea (void)   
{   
	for (int i = BA_1; i = BA_20; ++i)   
		addBallArea ((BallArea) i);   
}   

// public   
void   
	TeamOrder::addAllSpeed (void)   
{   
	for (int i = BS_LOW; i = BS_MORE_HIGH; ++i)   
		addBallSpeed ((BallSpeed) i);   
}   

// public   
void   
	TeamOrder::addAllDirection (void)   
{   
	for (int i = BD_REST; i = BD_RIGHT_BOTTOM; ++i)   
		addBallDirection ((BallDirection) i);   
}   

// public   
void   
	TeamOrder::addAllPower (void)   
{   
	for (int i = BP_OPPONENT; i = BP_WITHOUT; ++i)   
		addBallPower ((BallPower) i);          
}   

// public   
void   
	TeamOrder::addAllGuardLeak (void)   
{   
	for (int i = GL_OPPONENT_MORE_BIG; i = GL_SELF_MORE_BIG; ++i)   
		addGuardLeak ((GuardLeak) i);   
}   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// ��������   
//   

// public virtual   
bool   
	AttackTeam::initRoles (void)   
{   
	{   
		//   
		// Ϊ�˶��ΰ��Ž�ɫ   
		//   
		addRole (RT_GOALKEEPER, 0);         // ����Ա   
		addRole (RT_ATTACK, 1);             // ������ - ������·�ȴ���ϲ�����   
		addRole (RT_VANGUARD_TOP, 2);       // ��ǰ�� - ����ʱ�����ϰ����   
		addRole (RT_VANGUARD_BOTTOM, 3);    // ��ǰ�� - ����ʱ�����°����   
		addRole (RT_ATTACK_DEFEND, 4);      // �������� - ѡ���������ʱ������صĻ�����   
	}   
	return true;   
}   

// public virtual   
bool   
	AttackTeam::initCondition (void)   
{   
	{   
		//   
		// ��ӷ��ϵ�����   
		//   
		addBallArea (BA_3);   
		addBallArea (BA_4);   
		addBallArea (BA_5);   
		addBallArea (BA_8);   
		addBallArea (BA_9);   
		addBallArea (BA_10);   
		addBallArea (BA_13);   
		addBallArea (BA_14);   
		addBallArea (BA_15);   
		addBallArea (BA_18);   
		addBallArea (BA_19);   
		addBallArea (BA_20);   
	}   

	addAllSpeed ();                     // ��������ٶ�   
	addAllDirection ();                 // ������з���   
	addAllPower ();                     // ������п���Ȩ   
	addAllGuardLeak ();                 // �������©��   
	//{   
	//  //   
	//  // ��ӷ��ϵ�����ٶ�   
	//  //   
	//  addBallSpeed ();                   
	//}   

	//{   
	//  //   
	//  // ��ӷ��ϵ�����˶�����   
	//  //   
	//  addBallDirection ();   
	//}   

	//{   
	//  //   
	//  // ��ӷ��ϵ������Ȩ   
	//  //   
	//  addBallPower ();   
	//}   
	//   
	//{   
	//  //   
	//  // ��ӷ��ϵ�©�����   
	//  //   
	//  addGuardLeak ();   
	//}   
	return true;   
}   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// ���ض��� - TN_DEFEND   
//   

// public virtual   
bool   
	DefendTeam::initRoles (void)   
{   
	//   
	// Ϊ�˶��ΰ��Ž�ɫ   
	//   
	addRole (RT_GOALKEEPER, 0);         // ����Ա   
	addRole (RT_DEFEND_LEFT_TOP, 1);    // ���Ͻǵĺ���   
	addRole (RT_DEFEND_LEFT_BOT, 2);    // ���½ǵĺ���   
	addRole (RT_DEFEND_RIGHT_TOP, 3);   // ���Ͻǵĺ���   
	addRole (RT_DEFEND_RIGHT_BOT, 4);   // ���½ǵĺ���   
	return true;   
}   

// public virtual   
bool   
	DefendTeam::initCondition (void)   
{   
	{   
		//   
		// ��ӷ��ϵ�����   
		//   
		addBallArea (BA_1);   
		addBallArea (BA_2);   
		addBallArea (BA_6);   
		addBallArea (BA_7);   
		addBallArea (BA_11);   
		addBallArea (BA_12);   
		addBallArea (BA_16);   
		addBallArea (BA_17);   
	}   

	addAllSpeed ();                     // ��������ٶ�   
	addAllDirection ();                 // ������з���   
	addAllPower ();                     // ������п���Ȩ   
	addAllGuardLeak ();                 // �������©��   
	return true;   
}  


