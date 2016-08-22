/****************************************************************************************************  
teamorder.cpp 艾数机器人队形源文件  

Purpose:  
完成特定目的地队形分配，每个队形使用最合适的角色  


****************************************************************************************************/   

#include "area.h"   
#include "teamorder.h"   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// 队形管理   
//   

// public   
TeamManager::TeamManager (void)   
	: teams ()   
{   
	/********************************************************************************  
	//  
	// 添加所有的队形  
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
	// 初始化分配角色   
	//   
	if (team->initRoles () == false) {   
		//ASSERT (false);   
		;   
	}   

	//   
	// 初始化使用队形时所需要的状态条件   
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
	// 没有一个队形符合条件 .... 真惨，使用基本队形   
	//   
	return teams[0];   
}   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// 队形   
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
		roles[i] = RT_UNKNOWN; // 队形所需要的角色   
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
	// 检查是否符合条件   
	// 如果所有状态条件都符合则说明当前队形符合条件   
	//   
	{   
		//   
		// 区域检查   
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
		// 球速检查   
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
		// 球的运动方向   
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
		// 球的控制权   
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
		// 漏洞   
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
	// 所有条件都符合   
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
// 进攻队形   
//   

// public virtual   
bool   
	AttackTeam::initRoles (void)   
{   
	{   
		//   
		// 为此队形安排角色   
		//   
		addRole (RT_GOALKEEPER, 0);         // 守门员   
		addRole (RT_ATTACK, 1);             // 进攻者 - 负责中路等待配合并进攻   
		addRole (RT_VANGUARD_TOP, 2);       // 上前锋 - 进攻时负责上半个球场   
		addRole (RT_VANGUARD_BOTTOM, 3);    // 下前锋 - 进攻时负责下半个球场   
		addRole (RT_ATTACK_DEFEND, 4);      // 进攻后卫 - 选择进攻队形时负责防守的机器人   
	}   
	return true;   
}   

// public virtual   
bool   
	AttackTeam::initCondition (void)   
{   
	{   
		//   
		// 添加符合的区域   
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

	addAllSpeed ();                     // 添加所有速度   
	addAllDirection ();                 // 添加所有方向   
	addAllPower ();                     // 添加所有控制权   
	addAllGuardLeak ();                 // 添加所有漏洞   
	//{   
	//  //   
	//  // 添加符合的球的速度   
	//  //   
	//  addBallSpeed ();                   
	//}   

	//{   
	//  //   
	//  // 添加符合的球的运动方向   
	//  //   
	//  addBallDirection ();   
	//}   

	//{   
	//  //   
	//  // 添加符合的球控制权   
	//  //   
	//  addBallPower ();   
	//}   
	//   
	//{   
	//  //   
	//  // 添加符合的漏洞情况   
	//  //   
	//  addGuardLeak ();   
	//}   
	return true;   
}   

////////////////////////////////////////////////////////////////////////////////////////////////////   
//   
// 防守队形 - TN_DEFEND   
//   

// public virtual   
bool   
	DefendTeam::initRoles (void)   
{   
	//   
	// 为此队形安排角色   
	//   
	addRole (RT_GOALKEEPER, 0);         // 守门员   
	addRole (RT_DEFEND_LEFT_TOP, 1);    // 左上角的后卫   
	addRole (RT_DEFEND_LEFT_BOT, 2);    // 左下角的后卫   
	addRole (RT_DEFEND_RIGHT_TOP, 3);   // 右上角的后卫   
	addRole (RT_DEFEND_RIGHT_BOT, 4);   // 右下角的后卫   
	return true;   
}   

// public virtual   
bool   
	DefendTeam::initCondition (void)   
{   
	{   
		//   
		// 添加符合的区域   
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

	addAllSpeed ();                     // 添加所有速度   
	addAllDirection ();                 // 添加所有方向   
	addAllPower ();                     // 添加所有控制权   
	addAllGuardLeak ();                 // 添加所有漏洞   
	return true;   
}  


