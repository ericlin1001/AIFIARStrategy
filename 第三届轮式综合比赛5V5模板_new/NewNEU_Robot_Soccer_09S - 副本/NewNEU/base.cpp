/****************************************************************************************************  
base.cpp ����������������� ״̬��Ϣö����,���÷���  
  
Purpose:  
    ��ɫ����ʹ�õĶ���  
  
author:  
    yy_cn  
  
Created Time:  
    2006-5-8  
****************************************************************************************************/   
   
#include "base.h"   
   
//   
// analyseFieldInfo   
//   
BallField analyseFieldInfo (double x /* = -1.0 */)   
{   
    static BallField ballField = BF_UNKNOWN;   
    if (x != -1.0 && ballField == BF_UNKNOWN) {   
        if (x > FLEFTX && x  FORBIDDEN_ZONE_X)   
            ballField = BF_IS_LEFT;   
        else   
            ballField = BF_IS_RIGHT;   
    }   
       
    return ballField;   
}   
   
//   
// transform   
//   
void transform (double &x, double &y)   
{   
    //   
    // ������󷽳�������Ҫת��   
    //   
    if (analyseFieldInfo () == BF_IS_LEFT)   
        return;   
   
    //   
    // �ҷ�������Ҫת��   
    //   
    x = (FRIGHTX + FLEFTX) - x;   
    y = y;   
}   
   
//   
// transform   
//   
void transform (double &rotation)   
{   
    //   
    // ������󷽳�������Ҫת��   
    //   
    if (analyseFieldInfo () == BF_IS_LEFT)   
        return;   
   
    if (rotation  0)   
        rotation = rotation + 180;   
    else   
        rotation = 180 - rotation;   
}   
   
//   
// isComprise   
//   
bool isComprise (double topX, double topY, double botX, double botY, double pointX, double pointY)   
{   
    if (pointX >= topX && pointX = botX && pointY = topY && pointY >= botY)   
        return true;   
    return false;   
}   
   
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
                    ���� targetX  
                        |     #  
                        |    /| -  -  
                        |   /a| a1 |  
                        | @/--| -  a2  
                        | /b  |    |  
  ӳ��� targetY (*) -> +------    -  
                        |  |b1|  
                        |     |  
                        |--b2-|  
  
        # ����������  
        @ ������  
       (*) ��������������֮���ֱ��ӳ�䵽���� Y ���괦�ĵ�λ��  
  
       a1, b1, a2 ��֪���� b2  
  
       tan a = a1 / b1  
       tan b = a2 / b2  
       tan a == tan b  
  
       a1 / b1 == a2 / b2  
       b2 = (a1 / b1) * a2  
       ӳ��� Y = b2 + y1;  
     */   
    double a1 = y2 - y1;   
    double b1 = x1 - x2;   
    double a2 = x1 - targetX;   
   
    return (((a1 / b1) * a2) + y1);   
}   