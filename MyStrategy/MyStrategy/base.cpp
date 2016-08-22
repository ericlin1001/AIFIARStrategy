/****************************************************************************************************  
base.cpp 艾数机器人足球策略 状态信息枚举体,公用方法  
  
Purpose:  
    角色可以使用的动作  
  
author:  
    yy_cn  
  
Created Time:  
    2006-5-8  
****************************************************************************************************/   
   
#include "base.h"   
  #define NAME_CASE(m) case m:return #m
char *getRoleTypeName(RoleType t){
	switch(t){
	NAME_CASE(RT_GOALKEEPER);		// 守门员角色 
	NAME_CASE(RT_ATTACK);
	NAME_CASE(RT_VANGUARD_TOP);
	NAME_CASE(RT_VANGUARD_BOTTOM);
	NAME_CASE(RT_ATTACK_DEFEND);
	NAME_CASE(RT_DEFEND_LEFT_TOP);
	NAME_CASE(RT_DEFEND_LEFT_BOT);
	NAME_CASE(RT_DEFEND_RIGHT_TOP);
	NAME_CASE(RT_DEFEND_RIGHT_BOT);
	NAME_CASE(RT_UNKNOWN);
	}
	return "UNKNOW";
} 
//   
// analyseFieldInfo   
//   
/*BallField analyseFieldInfo (double x )   
{   
    static BallField ballField = BF_UNKNOWN;   
    if (x != -1.0 && ballField == BF_UNKNOWN) {   
        if (x > FLEFTX && x  FIELD_INFO::FORBIDDEN_AREA::getX())   
            ballField = BallField::LEFT;   
        else   
            ballField = BallField::RIGHT;   
    }   
       
    return ballField;   
}   */
   
//   
// transform   
// 
/*
void transform (double &x, double &y)   
{   
    //   
    // 如果在左方场地则不需要转换   
    //   
    if (analyseFieldInfo () == BallField::LEFT)   
        return;   
   
    //   
    // 右方场地需要转换   
    //   
    x = (FRIGHTX + FLEFTX) - x;   
    y = y;   
}   
   */
   
//   
// isComprise   
//   
/*bool isComprise (double topX, double topY, double botX, double botY, double pointX, double pointY)   
{   
    if (pointX >= topX && pointX <= botX && pointY = topY && pointY >= botY)   
        return true;   
    return false;   
}  */ 
   
//   
// getDistance   
//   
double getDistance (double x1, double y1, double x2, double y2)   
{   
    double x = x1 - x2;   
    double y = y1 - y2;   
       
    return sqrt (x * x + y * y);   
}   
   
//   
// getMappedTargetY   
//   
double getMappedTargetY (double x1, double y1, double x2, double y2, double targetX)   
{   
    /*  
                    给定 targetX  
                        |     #  
                        |    /| -  -  
                        |   /a| a1 |  
                        | @/--| -  a2  
                        | /b  |    |  
  映射点 targetY (*) -> +------    -  
                        |  |b1|  
                        |     |  
                        |--b2-|  
  
        # 机器人坐标  
        @ 球坐标  
       (*) 机器人与球两点之间的直线映射到球门 Y 坐标处的点位置  
  
       a1, b1, a2 已知，求 b2  
  
       tan a = a1 / b1  
       tan b = a2 / b2  
       tan a == tan b  
  
       a1 / b1 == a2 / b2  
       b2 = (a1 / b1) * a2  
       映射点 Y = b2 + y1;  
     */   
    double a1 = y2 - y1;   
    double b1 = x1 - x2;   
    double a2 = x1 - targetX;   
   
    return (((a1 / b1) * a2) + y1);   
}   