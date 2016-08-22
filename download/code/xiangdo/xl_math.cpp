    #include "xL_math.h"   
       
       
    /*! �ж�һ�����ķ���.  
    ���� d�����жϵ���  
    ���أ�dΪ��������1,���򷵻�-1 */   
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
    // �Ƕȣ����Ǻ�����صĺ���   
    ////////////////////////////////////////////////////////////////////   
       
    /*! �������ƽǶ�ת��Ϊ�Ƕ��ƽǶ�  
    ���� x: ��λΪ����  
    ����  : ���صȼ۵ĽǶ��ƽǶ�   */   
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
       
    /* ���Ƕȹ�񻯵� [0,360)��Χ��  
    ���أ���񻯺�ĽǶ� */   
    const AngDeg NormalizeAngle_360(AngDeg &ang)   
    {   
        while (ang  0.0) ang += 360.0;   
        while (ang >= 360.0) ang -= 360.0;   
        return (ang);   
    }   
       
    /* ���Ƕȹ�񻯵� [0,2*PI)��Χ��  
    ���أ���񻯺�ĽǶ� */      
    const AngRad NormalizeRadian_2PI(AngRad &rad)   
    {   
        while (rad  0.0) rad += PIx2;   
        while (rad >= PIx2) rad -= PIx2;   
        return rad;   
    }   
       
    /* ���Ƕȹ�񻯵� (-180,180]��Χ��  
    ���أ���񻯺�ĽǶ� */      
    const AngDeg NormalizeAngle_180(AngDeg &ang)   
    {   
        while (ang = -180.0) ang += 360.0;   
        while (ang > 180.0) ang -= 360.0;   
        return (ang);   
    }   
       
    /* ���Ƕȹ�񻯵� (-PI,PI]��Χ��  
    ���أ���񻯺�ĽǶ� */      
    const AngRad  NormalizeRadian_PI(AngRad &rad)   
    {   
        while (rad = -PI) rad += PIx2;   
        while (rad > PI) rad -= PIx2;   
        return rad;   
    }   
       
    /* һ���ǵ������ߵĽǶȷֱ�Ϊangle1,angle2,��˽ǵĽ�ƽ���߽Ƕ�  
    �磬�����ߵĽǶȷֱ�Ϊ350��50�����ƽ���߽Ƕ�Ϊ20  
    ����:��ƽ���߽Ƕȣ��ҷ�Χ��[0,360) */   
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
    // ��ά������صĺ���   
    ////////////////////////////////////////////////////////////////////   
       
       
    //���ؾ��������ľ���   
    const double VectorsDist(const Vector &vec1,const Vector &vec2)   
    {   
        return sqrt( Square(vec1.x - vec2.x) + Square(vec1.y - vec2.y) );   
    }   
       
    //���ؾ��������ľ���ƽ��   
    const double VectorsDistSquare(const Vector &vec1,const Vector &vec2)   
    {   
        return  Square(vec1.x - vec2.x) + Square(vec1.y - vec2.y);   
    }   
       
    //������������   
    const double VectorLength(const Vector &vec)   
    {   
        return sqrt( (vec.x* vec.x) + (vec.y * vec.y) );   
    }   
       
    //������������ƽ��   
    const double VectorLengthSquare(const Vector &vec)   
    {   
        return vec.x* vec.x + vec.y * vec.y;   
    }   
       
    //����������Ӧ�ĽǶ�,[0,360)   
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
       
    //����һ�������ĵ�λ������   
    const Vector  VectorNormalize(Vector &vec)   
    {   
        vec.x = 1;   
        vec.y = 0;   
        double length = VectorLength(vec);   
        if(length  EPSILON) return vec;   
        VectorDivid(vec,length);   
        return vec;   
    }   
       
    //����Vector���   
    const Vector VectorAdd(Vector &vec1,const Vector &vec2)   
    {   
        vec1.x +=  vec2.x;   
        vec1.y +=  vec2.y;   
        return vec1;   
    }   
       
       
    /* ��������Vector���  
    ���� minuend��������  
    ���� subtrahend������  
    ���أ�����Vector֮��*/   
    const Vector VectorSub( Vector &minuend,const Vector &subtrahend)   
    {   
        minuend.x -=  subtrahend.x;   
        minuend.y -=  subtrahend.y;   
        return minuend;   
    }   
       
    /* ����ʸ��������ĳ˻�  
    ����vec��ʸ��  
    ����multiple������  
    ���أ�ʸ���������˺�õ���ʸ��*/   
    const Vector VectorMultiply( Vector &vec,const double multiple)   
    {   
        vec.x *= multiple;   
        vec.y *= multiple;   
        return vec;   
    }   
       
       
    /* ����ʸ������������  
    ����vec��ʸ����������  
    ����divisor������,����  
    ���أ�ʸ�����Ա�����õ���ʸ��*/   
    const Vector VectorDivid( Vector &vec,const double divisor)   
    {   
        vec.x /=  divisor;   
        vec.y /= divisor;   
        return vec;   
    }   
       
    // ������������(���)   
    const double VectorDot(const Vector &vec1,const Vector &vec2)   
    {   
        return  vec1.x * vec2.x + vec1.y*vec2.y;   
    }   
       
    // ������ʸ����(���)   
    const double VectorCross(const Vector &vec1,const Vector &vec2)   
    {   
        return  vec1.x * vec2.y - vec1.y*vec2.x;   
    }   
       
    //���������ļн�,[0,180)   
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