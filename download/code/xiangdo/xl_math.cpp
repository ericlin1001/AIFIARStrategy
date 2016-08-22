    #include "xL_math.h"   
       
       
    /*! 判断一个数的符号.  
    参数 d：所判断的数  
    返回：d为正数返回1,否则返回-1 */   
    int Sign( double d )   
    {   
        return (d>0)?1:-1;   
    }   
       
    const double Clamp(double& val, const double min, const double max)   
    {   
        if (val<min) val=min;    
        if (val>max) val=max;   
        return val;   
    }   
       
    const double MaxLimit(double& val, const double max)   
    {   
        if (val>max) val=max;    
        return val;   
    }   
       
    const double MinLimit(double& val, const double min)   
    {   
        if (val<min) val=min;   
        return val;   
    }   
       
       
    /////////////////////////////////////////////////////////////////////   
    // 角度，三角函数相关的函数   
    ////////////////////////////////////////////////////////////////////   
       
    /*! 将弧度制角度转换为角度制角度  
    参数 x: 单位为弧度  
    返回  : 返回等价的角度制角度   */   
    AngDeg RadToDeg( AngRad x )   
    {   
      return ( x * DegPerRad );   
    }   
       
    /*! This function converts an angle in degrees to the corresponding angle in  
        radians.  
        \param x an angle in degrees  
        \return the corresponding angle in radians */   
    AngRad DegToRad( AngDeg x )   
    {   
      return ( x * RadPerDeg );   
    }   
       
    /*! This function returns the cosine of a given angle in degrees using the  
        built-in cosine function that works with angles in radians.  
        \param x an angle in degrees  
        \return the cosine of the given angle */   
    double CosDeg( AngDeg x )   
    {   
      return ( cos( DegToRad( x ) ) );   
    }   
       
    /*! This function returns the sine of a given angle in degrees using the  
        built-in sine function that works with angles in radians.  
        \param x an angle in degrees  
        \return the sine of the given angle */   
    double SinDeg( AngDeg x )   
    {   
      return ( sin( DegToRad( x ) ) );   
    }   
       
    /*! This function returns the tangent of a given angle in degrees using the  
        built-in tangent function that works with angles in radians.  
        \param x an angle in degrees  
        \return the tangent of the given angle */   
    double TanDeg( AngDeg x )   
    {   
      return ( tan( DegToRad( x ) ) );   
    }   
       
    /*! This function returns the principal value of the arc tangent of x  
        in degrees using the built-in arc tangent function which returns  
        this value in radians.  
        \param x a double value  
        \return the arc tangent of the given value in degrees */   
    AngDeg AtanDeg( double x )   
    {   
      return ( RadToDeg( atan( x ) ) );   
    }   
       
    /*! This function returns the principal value of the arc tangent of y/x in  
        degrees using the signs of both arguments to determine the quadrant of the  
        return value. For this the built-in 'atan2' function is used which returns  
        this value in radians.  
        \param x a double value  
        \param y a double value  
        \return the arc tangent of y/x in degrees taking the signs of x and y into  
        account */   
    double Atan2Deg( double x, double y )   
    {   
      if( fabs( x )  EPSILON && fabs( y )  EPSILON )   
        return ( 0.0 );   
       
      return ( RadToDeg( atan2( x, y ) ) );   
    }   
       
    /*! This function returns the principal value of the arc cosine of x in degrees  
        using the built-in arc cosine function which returns this value in radians.  
        \param x a double value  
        \return the arc cosine of the given value in degrees */   
    AngDeg AcosDeg( double x )   
    {   
      if( x >= 1 )   
        return ( 0.0 );   
      else if( x = -1 )   
        return ( 180.0 );   
       
      return ( RadToDeg( acos( x ) ) );   
    }   
       
    /*! This function returns the principal value of the arc sine of x in degrees  
        using the built-in arc sine function which returns this value in radians.  
        \param x a double value  
        \return the arc sine of the given value in degrees */   
    AngDeg AsinDeg( double x )   
    {   
      if( x >= 1 )   
        return ( 90.0 );   
      else if ( x = -1 )   
        return ( -90.0 );   
       
      return ( RadToDeg( asin( x ) ) );   
    }   
       
    /* 将角度规格化到 [0,360)范围内  
    返回：规格化后的角度 */   
    const AngDeg NormalizeAngle_360(AngDeg &ang)   
    {   
        while (ang  0.0) ang += 360.0;   
        while (ang >= 360.0) ang -= 360.0;   
        return (ang);   
    }   
       
    /* 将角度规格化到 [0,2*PI)范围内  
    返回：规格化后的角度 */      
    const AngRad NormalizeRadian_2PI(AngRad &rad)   
    {   
        while (rad  0.0) rad += PIx2;   
        while (rad >= PIx2) rad -= PIx2;   
        return rad;   
    }   
       
    /* 将角度规格化到 (-180,180]范围内  
    返回：规格化后的角度 */      
    const AngDeg NormalizeAngle_180(AngDeg &ang)   
    {   
        while (ang = -180.0) ang += 360.0;   
        while (ang > 180.0) ang -= 360.0;   
        return (ang);   
    }   
       
    /* 将角度规格化到 (-PI,PI]范围内  
    返回：规格化后的角度 */      
    const AngRad  NormalizeRadian_PI(AngRad &rad)   
    {   
        while (rad = -PI) rad += PIx2;   
        while (rad > PI) rad -= PIx2;   
        return rad;   
    }   
       
    /* 一个角的两个边的角度分别为angle1,angle2,求此角的角平分线角度  
    如，两个边的角度分别为350和50，则角平分线角度为20  
    返回:角平分线角度，且范围在[0,360) */   
    const  AngDeg BisectorAngle(AngDeg side1Ang,AngDeg side2Ang)   
    {   
        AngDeg averageAngle;   
        NormalizeAngle_360(side1Ang);   
        NormalizeAngle_360(side2Ang);   
        averageAngle = (side1Ang + side2Ang)/2.0;   
       
        if (fabs(side1Ang - side2Ang) >180.0)   
        {   
            averageAngle += 180;   
            NormalizeAngle_360(averageAngle);   
        }   
        return averageAngle;   
    }   
       
       
       
    /////////////////////////////////////////////////////////////////////   
    // 二维向量相关的函数   
    ////////////////////////////////////////////////////////////////////   
       
       
    //返回据两个点间的距离   
    const double VectorsDist(const Vector &vec1,const Vector &vec2)   
    {   
        return sqrt( Square(vec1.x - vec2.x) + Square(vec1.y - vec2.y) );   
    }   
       
    //返回据两个点间的距离平方   
    const double VectorsDistSquare(const Vector &vec1,const Vector &vec2)   
    {   
        return  Square(vec1.x - vec2.x) + Square(vec1.y - vec2.y);   
    }   
       
    //返回向量长度   
    const double VectorLength(const Vector &vec)   
    {   
        return sqrt( (vec.x* vec.x) + (vec.y * vec.y) );   
    }   
       
    //返回向量长度平方   
    const double VectorLengthSquare(const Vector &vec)   
    {   
        return vec.x* vec.x + vec.y * vec.y;   
    }   
       
    //返回向量对应的角度,[0,360)   
    const AngDeg VectorAngle(const Vector &vec)   
    {   
        double ang = Atan2Deg(vec.x,vec.y);   
        if(ang  0) ang += 360.0;    
        return ang;   
    }   
       
    const Vector GetVectorByPolar(double len,AngDeg ang)   
    {   
        Vector result;   
        result.x = len * CosDeg(ang);   
        result.y = len * SinDeg(ang);   
        return result;   
    }   
       
    //返回一个向量的单位化向量   
    const Vector  VectorNormalize(Vector &vec)   
    {   
        vec.x = 1;   
        vec.y = 0;   
        double length = VectorLength(vec);   
        if(length  EPSILON) return vec;   
        VectorDivid(vec,length);   
        return vec;   
    }   
       
    //两个Vector相加   
    const Vector VectorAdd(Vector &vec1,const Vector &vec2)   
    {   
        vec1.x +=  vec2.x;   
        vec1.y +=  vec2.y;   
        return vec1;   
    }   
       
       
    /* 计算两个Vector相减  
    参数 minuend：被减数  
    参数 subtrahend：减数  
    返回：两个Vector之差*/   
    const Vector VectorSub( Vector &minuend,const Vector &subtrahend)   
    {   
        minuend.x -=  subtrahend.x;   
        minuend.y -=  subtrahend.y;   
        return minuend;   
    }   
       
    /* 计算矢量与标量的乘积  
    参数vec：矢量  
    参数multiple：标量  
    返回：矢量与标量相乘后得到的矢量*/   
    const Vector VectorMultiply( Vector &vec,const double multiple)   
    {   
        vec.x *= multiple;   
        vec.y *= multiple;   
        return vec;   
    }   
       
       
    /* 计算矢量与标量的相除  
    参数vec：矢量，被除数  
    参数divisor：标量,除数  
    返回：矢量除以标量后得到的矢量*/   
    const Vector VectorDivid( Vector &vec,const double divisor)   
    {   
        vec.x /=  divisor;   
        vec.y /= divisor;   
        return vec;   
    }   
       
    // 向量的数量积(点乘)   
    const double VectorDot(const Vector &vec1,const Vector &vec2)   
    {   
        return  vec1.x * vec2.x + vec1.y*vec2.y;   
    }   
       
    // 向量的矢量积(差乘)   
    const double VectorCross(const Vector &vec1,const Vector &vec2)   
    {   
        return  vec1.x * vec2.y - vec1.y*vec2.x;   
    }   
       
    //两个向量的夹角,[0,180)   
    const AngDeg AngleOf2Vector(const Vector &vec1,const Vector &vec2)   
    {   
        double d = VectorLength(vec1) * VectorLength(vec2);   
        if(d EPSILON) return 0.0;   
        return AcosDeg(VectorDot(vec1,vec2)/d);   
    }   
       
    const double CosValueOf2Vector(Vector vec1, Vector vec2)   
    {   
        VectorNormalize(vec1);   
        VectorNormalize(vec2);   
        return VectorDot(vec1,vec2);   
    }   
       
    const double SinValueOf2Vector(Vector vec1, Vector vec2)   
    {   
        VectorNormalize(vec1);   
        VectorNormalize(vec2);   
        return VectorCross(vec1,vec2);   
    }   