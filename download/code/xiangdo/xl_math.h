#ifndef _XL_MATH_H_ 
#define _XL_MATH_H_ 
#include <math.h> 
#include "xl_global.h" 
 
typedef double AngDeg; 
typedef double AngRad; 
 
const double PI    = 3.14159265359; 
const double PIx2 = PI*2.0; 
const double PI_2 = PI/2.0; 
const double PI_4 = PI/4.0; 
const double RadPerDeg = PI/180.0; 
const double DegPerRad = 180.0/PI; 
 
//�жϸ�������ͬʱ�ľ��� 
#define EPSILON 0.00001 
 
#ifndef Square 
#define Square(a) ((a)*(a)) 
#endif 
 
#ifndef Min 
#define Min(a,b) (((a)<(b))?(a):(b)) 
#endif 
 
#ifndef Max 
#define Max(a,b) (((a)>(b))?(a):(b)) 
#endif 
 
 
int    Sign    ( double d            ); 
 
 
///////////////////////////////////////////////////////////////////// 
// �Ƕȣ����Ǻ�����صĺ��� 
//////////////////////////////////////////////////////////////////// 
AngDeg RadToDeg( AngRad x             ); 
AngRad DegToRad( AngDeg x             ); 
double CosDeg  ( AngDeg x             ); 
double SinDeg  ( AngDeg x             ); 
double TanDeg  ( AngDeg x             ); 
AngDeg AtanDeg ( double x             ); 
double Atan2Deg( double x,  double y  ); 
AngDeg AcosDeg ( double x             ); 
AngDeg AsinDeg ( double x             ); 
 
const AngDeg NormalizeAngle_360 (AngDeg  &ang); 
const AngRad NormalizeRadian_2PI(AngRad  &rad); 
const AngDeg NormalizeAngle_180 (AngDeg  &ang); 
const AngRad NormalizeRadian_PI (AngRad  &rad); 
const AngDeg BisectorAngle      (AngDeg side1Ang,AngDeg side2Ang); 
 
 
///////////////////////////////////////////////////////////////////// 
// ��ά������صĺ��� 
//////////////////////////////////////////////////////////////////// 
 
const Vector GetVectorByPolar(double len,AngDeg ang); 
 
const double VectorsDist(const Vector &vec1,const Vector &vec2); 
 
const double VectorsDistSquare(const Vector &vec1,const Vector &vec2); 
 
const AngDeg VectorAngle(const Vector &vec); 
 
const double VectorLength(const Vector &vec); 
 
const double VectorLengthSquare(const Vector &vec); 
 
//ʸ��vec��λ�� 
const Vector VectorNormalize(Vector &vec); 
 
//ʸ��vec1����vec2,���������vec1,����vec1 
const Vector VectorAdd(Vector &vec1,const Vector &vec2); 
 
//ʸ��minuendc��ȥsubtrahend,���������minuend,ͬʱ����minuend 
const Vector VectorSub(Vector &minuend,const Vector &subtrahend); 
 
//ʸ��vec����multiple,���������vec,����vec 
const Vector VectorMultiply(Vector &vec,const double multiple); 
 
//ʸ��vec����divisor,���������vec,����vec 
const Vector VectorDivid(Vector &vec,const double divisor); 
 
//���ƽ���߽Ƕ� 
const  AngDeg BisectorAngle(AngDeg side1Ang,AngDeg side2Ang); 
 
const double VectorCross(const Vector &vec1,const Vector &vec2); 
 
const double VectorDot(const Vector &vec1,const Vector &vec2); 
 
const double CosValueOf2Vector(Vector vec1, Vector vec2); 
 
const double SinValueOf2Vector(Vector vec1, Vector vec2); 
 
#endif 