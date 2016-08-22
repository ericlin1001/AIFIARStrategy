#ifndef NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_
#define NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_

#include "base.h"
#include "GeometryR.h"



class Object {
public:
	Object();
	Object(const VecPosition &position, 
		const VecPosition &vec, 
		double theta);
	explicit Object(const Object &object);
	virtual ~Object() {}
	virtual void reset();//this reset all param to the initial state!

	inline double GetDistanceTo(const VecPosition &target)const {return this->_position.GetDistanceTo(target);}
	inline const VecPosition & getPosition()const { return _position;}
	inline const VecPosition & getVector()const { return _vector; }
	inline double getTheta()const { return _theta; }
	inline VecPosition getDirection()const{VecPosition dir(1,0);dir=dir.Rotate(getTheta());return dir;}
	//
	inline void setPosition(const VecPosition &position) { this->_position = position; }
	inline void setPosition(const double x,const double y, CoordSystemT cs = CARTESIAN) {this->_position.SetVecPosition(x, y, cs); }
	void setVector(const VecPosition &vec) { this->_vector = vec; }
	void setVector(double x, double y, CoordSystemT cs = CARTESIAN) {this->_vector.SetVecPosition(x, y, cs); }
	void setTheta(double theta) { theta = VecPosition::NormalizeAngle(theta); }
	void setNewPosition(double x, double y, CoordSystemT cs = CARTESIAN){setVector(x - this->_position.GetX(),y - this->_position.GetY());setPosition(x,y,cs);}
private:
	VecPosition _position;//
	VecPosition _vector;//speed
	double _theta; //unit:rad
	// Disallow assign
	void operator= (const Object &) {}
};

class BallBasis : public Object {//add the history function
public:
	BallBasis();
	BallBasis(const VecPosition &position, 
		const VecPosition &vec, 
		double theta);
	explicit BallBasis(const Object &object);
	explicit BallBasis(const BallBasis &ballbasis);
	virtual ~BallBasis() {}
	//
	virtual void Update(const VecPosition &position ,double theta);
	virtual void reset();//this reset all param to the initial state!
	//
	const VecPosition & getOldPosition(const unsigned index)const {return this->getOldData(index).position;}
	const VecPosition & getOldVector(const unsigned index)const {return  this->getOldData(index).vector; }
	const double getOldTheta(const unsigned index)const {return  this->getOldData(index).theta; }
	const Old_Data& getOldData(const unsigned index)const{return index < OLD_DATA_NUM ? _oldData[index]: _oldData[OLD_DATA_NUM - 1];
	//
private:
	//
	enum { OLD_DATA_NUM = 3 };
	/*VecPosition _oldPosition[OLD_DATA_NUM];
	VecPosition _oldVector[OLD_DATA_NUM];
	double _oldTheta[OLD_DATA_NUM];*/
	struct Old_Data{
		VecPosition position;
		VecPosition vector;
		double theta;
	};
	Old_Data _oldData[OLD_DATA_NUM];
	// Disallow assign
	void operator= (const BallBasis &) {}
};

class RobotBasis : public Object {
public://this class basically add the history!
	RobotBasis();
	RobotBasis(const VecPosition &position,const VecPosition &vec,double theta);
	explicit RobotBasis(const Object &object);
	explicit RobotBasis(const RobotBasis &robotbasis);
	virtual ~RobotBasis() {}

	virtual void Update(const VecPosition &position,double theta);//the important method
	virtual void reset();//this reset all param to the initial state!

	double getLeftVelocity()const { return _leftVelocity; }
	double getRightVelocity()const { return _rightVelocity; }
	//
	const VecPosition & getOldPosition(const unsigned index)const {return this->getOldData(index).position; }
	const VecPosition & getOldVector(const unsigned index)const {return this->getOldData(index).vector; }
	double getOldTheta(const unsigned index)const {return this->getOldData(index).theta; }
	double getOldLeftVelocity(const unsigned index)const {return this->getOldData(index).leftVeclocity; }
	double getOldRightVelocity(const unsigned index)const {return this->getOldData(index).rightVeclocity; }
	const Old_Data& getOldData(const unsigned index)const{return index < OLD_DATA_NUM ? _oldData[index]: _oldData[OLD_DATA_NUM - 1];
	//
	void setLeftVelocity(double left_velocity) { leftVelocity = left_velocity; }
	void setRightVelocity(double right_velocity) {rightVelocity = right_velocity; }
	
	void LimitSpeed(double max_speed=ROBOT_INFO::WHEEL::MAX_SPEED);
private:
	enum { OLD_DATA_NUM = 3 };
	double _leftVelocity;
	double _rightVelocity;
	//the history:
	/*VecPosition oldPosition[OLD_DATA_NUM];
	VecPosition oldVector[OLD_DATA_NUM];
	double oldTheta[OLD_DATA_NUM];
	double oldLeftVelocity[OLD_DATA_NUM];
	double oldRightVelocity[OLD_DATA_NUM];*/
	//
	struct Old_Data{
		VecPosition position;
		VecPosition vector;
		double theta;
		double leftVeclocity;
		double rightVeclocity;
	};
	Old_Data _oldData[OLD_DATA_NUM];
	// Disallow copy and assign
	void operator= (const RobotBasis &) {}
};

class RobotPID : public RobotBasis {
public:
	enum PID_Parameter_Index{ P = 0, I = 1, D = 2 };

	RobotPID();
	RobotPID(const VecPosition &position,const VecPosition &vec,double theta);
	explicit RobotPID(const Object &object);
	explicit RobotPID(const RobotBasis &robotbasis);
	explicit RobotPID(const RobotPID &robotPID);
	virtual ~RobotPID() {}

	virtual void Update(const VecPosition &position,double theta);
	virtual void reset();//this reset all param to the initial state!

	void ToPositionPD(VecPosition target, double speed);
	void TurnToAngle(double direction);

	/*double getToPositionPDAngularParameter(PID_Parameter_Index index)const {return ToPositionPDAngularParameter[index]; }
	double getToPositionPDLinearParameter(PID_Parameter_Index index)const {return ToPositionPDLinearParameter[index]; }
	double getTurnToAngleAngularParameter(PID_Parameter_Index index)const {return TurnToAngleAngularParameter[index]; }*/
	
	/*void setToPositionPDAngularParameter(double parameter,PID_Parameter_Index index) {ToPositionPDAngularParameter[index] = parameter; }
	void setToPositionPDLinearParameter(double parameter,PID_Parameter_Index index) {ToPositionPDLinearParameter[index] = parameter; }
	void setTurnToAngleAngularParameter(double parameter,PID_Parameter_Index index) {TurnToAngleAngularParameter[index] = parameter; }*/
protected:
	
private://auxiliary method:
	void setDesiredSpeed(double linearSpeed,double angularSpeed){
		setLeftVelocity(linearSpeed - ROBOT_INFO::HALF_LENGTH * angularSpeed);
		setRightVelocity(linearSpeed + ROBOT_INFO::HALF_LENGTH * angularSpeed);
		LimitSpeed(ROBOT_INFO::WHEEL::MAX_SPEED);
	}
private:
	enum { OLD_PID_DATA_NUM = 1 };
	enum { PID_PARAMETER_NUM = 3 };
	enum { NO_ACTION = 0, TO_POSITION_PD = 1, TURN_TO_ANGLE = 2 };
	unsigned int updateMode;

	void SetPIDParameter();//init the PID params,is invoked in constructor.

	void SaveParamToPositionPD();
	void SaveParamTurnToAngle();

	void ResetParamToPositionPD();
	void ResetParamTurnToAngle();
	// Update flag
	

	// PID parameter of ToPositionPD()
	double ToPositionPDAngularParameter[PID_PARAMETER_NUM];
	double ToPositionPDLinearParameter[PID_PARAMETER_NUM];

	// Current PID data of ToPositionPD()
	double ToPositionPDAngularDistance;
	double ToPositionPDLinearDistance;
	VecPosition ToPositionPDTarget;

	// Old PID data of ToPositionPD()
	double ToPositionPDOldAngularDistance[OLD_PID_DATA_NUM];
	double ToPositionPDOldLinearDistance[OLD_PID_DATA_NUM];
	VecPosition ToPositionPDOldTarget[OLD_PID_DATA_NUM];


	// PID parameter of TurnToAngle()
	double TurnToAngleAngularParameter[PID_PARAMETER_NUM];
	// Current PID data of TurnToAngle()
	double TurnToAngleAngularDistance;
	double TurnToAngleAngularDirection;

	// Old PID data of TurnToAngle()
	double TurnToAngleOldAngularDistance[OLD_PID_DATA_NUM];
	double TurnToAngleOldAngularDirection[OLD_PID_DATA_NUM];
	// Disallow copy and assign
	void operator= (const RobotPID &) {}
};
/*
class RobotSimple : public RobotBasis {
public:
	RobotSimple() : RobotBasis() {}
	RobotSimple(const VecPosition &position,
		const VecPosition &vec,
		double theta) : RobotBasis(position, vec, theta) {}
	explicit RobotSimple(const Object &object) : RobotBasis(object) {}
	explicit RobotSimple(const RobotBasis &robotbasis) 
		: RobotBasis(robotbasis) {}
	explicit RobotSimple(const RobotSimple &robotsimple) 
		: RobotBasis(robotsimple.getPosition(),
		robotsimple.getVector(),
		robotsimple.getTheta()) {}
	virtual ~RobotSimple() {}

	void SightChase(const VecPosition &target);
	void Intercept(const Object &object);
	void PotentialFunction(const VecPosition &target);
};*/

#endif  // NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_