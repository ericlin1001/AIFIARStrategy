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
 
//判断浮点数相同时的精度 
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
// 角度，三角函数相关的函数 
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
// 二维向量相关的函数 
//////////////////////////////////////////////////////////////////// 
 
const Vector GetVectorByPolar(double len,AngDeg ang); 
 
const double VectorsDist(const Vector &vec1,const Vector &vec2); 
 
const double VectorsDistSquare(const Vector &vec1,const Vector &vec2); 
 
const AngDeg VectorAngle(const Vector &vec); 
 
const double VectorLength(const Vector &vec); 
 
const double VectorLengthSquare(const Vector &vec); 
 
//矢量vec单位化 
const Vector VectorNormalize(Vector &vec); 
 
//矢量vec1加上vec2,结果保存在vec1,返回vec1 
const Vector VectorAdd(Vector &vec1,const Vector &vec2); 
 
//矢量minuendc减去subtrahend,结果保存在minuend,同时返回minuend 
const Vector VectorSub(Vector &minuend,const Vector &subtrahend); 
 
//矢量vec乘以multiple,结果保存在vec,返回vec 
const Vector VectorMultiply(Vector &vec,const double multiple); 
 
//矢量vec除以divisor,结果保存在vec,返回vec 
const Vector VectorDivid(Vector &vec,const double divisor); 
 
//求角平分线角度 
const  AngDeg BisectorAngle(AngDeg side1Ang,AngDeg side2Ang); 
 
const double VectorCross(const Vector &vec1,const Vector &vec2); 
 
const double VectorDot(const Vector &vec1,const Vector &vec2); 
 
const double CosValueOf2Vector(Vector vec1, Vector vec2); 
 
const double SinValueOf2Vector(Vector vec1, Vector vec2); 
 
#endif 