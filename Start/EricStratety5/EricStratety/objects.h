#ifndef NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_
#define NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_

#include "GeometryR.h"
#include "base.h"
#include "scripting_system.h"
#include "logger.h"

// By Code_B_Silence, NEU China
const double DEFAULT_BALL_SIZE = 2.0;
const double DEFAULT_ROBOT_SIZE = 4.0;
const double DEFAULT_ROBOT_SPEED_LIMIT = 100.0;

class Object {
 public:
  Object();
  Object(const VecPosition &position, 
         const VecPosition &vec, 
         double theta);
  explicit Object(const Object &object);
  virtual ~Object() {}
  
  double GetDistanceTo(const VecPosition &target) {
      return position_.GetDistanceTo(target); }
  
  const VecPosition & get_position()const { return position_;}
  void set_position(const VecPosition &position) { position_ = position; }
  void set_position(double x, double y, CoordSystemT cs = CARTESIAN) { 
    position_.SetVecPosition(x, y, cs); }
  const VecPosition & get_vector()const { return vector_; }
  void set_vector(const VecPosition &vec) { vector_ = vec; }
  void set_vector(double x, double y, CoordSystemT cs = CARTESIAN) { 
    vector_.SetVecPosition(x, y, cs); }
  double get_theta()const { return theta_; }
  void set_theta(double theta) { theta_ = VecPosition::NormalizeAngle(theta); }
  VecPosition getDirection()const{return VecPosition::GetVecPositionFromPolar(1,theta_);}
 private:
  VecPosition position_;
  VecPosition vector_;
  double theta_; 

  // Disallow assign
  void operator= (const Object &) {}

};

class BallBasis : public Object {
 public:
  BallBasis();
  BallBasis(const VecPosition &position, 
            const VecPosition &vec, 
            double theta);
  explicit BallBasis(const Object &object);
  explicit BallBasis(const BallBasis &ballbasis);
  virtual ~BallBasis() {}

  virtual void Update(const VecPosition &position, 
                      const VecPosition &vec, 
                      double theta);

  const VecPosition & get_old_position(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_position_[index]
                                : old_position_[OLD_DATA_NUM - 1]; }
  const VecPosition & get_old_vector(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_vector_[index]
                                : old_vector_[OLD_DATA_NUM - 1]; }
  double get_old_theta(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_theta_[index]
                                : old_theta_[OLD_DATA_NUM - 1]; }
  double get_ball_size()const { return ball_size_; }
  void set_ball_size(double radius) { ball_size_ = radius; }

 private:
  enum { OLD_DATA_NUM = 3 };
  VecPosition old_position_[OLD_DATA_NUM];
  VecPosition old_vector_[OLD_DATA_NUM];
  double old_theta_[OLD_DATA_NUM];
  double ball_size_;

  // Disallow assign
  void operator= (const BallBasis &) {}
};

class RobotBasis : public Object {
 public:
  RobotBasis();
  RobotBasis(const VecPosition &position, 
             const VecPosition &vec, 
             double theta);
  explicit RobotBasis(const Object &object);
  explicit RobotBasis(const RobotBasis &robotbasis);
  virtual ~RobotBasis() {}

  virtual void Update(const VecPosition &position, 
                      const VecPosition &vec, 
                      double theta);

  double get_left_velocity()const { return left_velocity_; }
  void set_left_velocity(double left_velocity) { 
    left_velocity_ = left_velocity; }
  double get_right_velocity()const { return right_velocity_; }
  void set_right_velocity(double right_velocity) { 
    right_velocity_ = right_velocity; }
  const VecPosition & get_old_position(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_position_[index]
                                : old_position_[OLD_DATA_NUM - 1]; }
  const VecPosition & get_old_vector(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_vector_[index]
                                : old_vector_[OLD_DATA_NUM - 1]; }
  double get_old_theta(unsigned index)const { 
    return index < OLD_DATA_NUM ? old_theta_[index]
                                : old_theta_[OLD_DATA_NUM - 1]; }
  double get_old_left_velocity(unsigned index)const {
    return index < OLD_DATA_NUM ? old_left_velocity_[index]
                                : old_left_velocity_[OLD_DATA_NUM - 1]; }
  double get_old_right_velocity(unsigned index)const {
    return index < OLD_DATA_NUM ? old_right_velocity_[index]
                                : old_right_velocity_[OLD_DATA_NUM - 1]; }
  double get_robot_size()const { return robot_size_; }
  void set_robot_size(double length) { robot_size_ = length; }
  double get_speed_limit()const { return speed_limit_; }
  void set_speed_limit(double limit) { speed_limit_ = limit; }
  
 private:
  enum { OLD_DATA_NUM = 3 };
  double left_velocity_;
  double right_velocity_;
  VecPosition old_position_[OLD_DATA_NUM];
  VecPosition old_vector_[OLD_DATA_NUM];
  double old_theta_[OLD_DATA_NUM];
  double old_left_velocity_[OLD_DATA_NUM];
  double old_right_velocity_[OLD_DATA_NUM];
  double robot_size_;
  double speed_limit_;

  // Disallow copy and assign
  void operator= (const RobotBasis &) {}
};

class RobotPID : public RobotBasis {
 public:
  enum PID_Parameter_Index{ P = 0, I = 1, D = 2 };

  RobotPID();
  RobotPID(const VecPosition &position,
           const VecPosition &vec,
           double theta);
  explicit RobotPID(const Object &object);
  explicit RobotPID(const RobotBasis &robotbasis);
  explicit RobotPID(const RobotPID &robotPID);
  virtual ~RobotPID() {}
  
  virtual void Update(const VecPosition &position,
                      const VecPosition &vec,
                      double theta);
  void ToPositionPD(VecPosition target, double speed=ROBOT_INFO::WHEEL::MAX_SPEED);
  void TurnToAngle(double direction);

  double get_ToPositionPD_angular_parameter(PID_Parameter_Index index)const {
    return ToPositionPD_angular_parameter_[index]; }
  void set_ToPositionPD_angular_parameter(double parameter, 
                                          PID_Parameter_Index index) {
    ToPositionPD_angular_parameter_[index] = parameter; }
  double get_ToPositionPD_linear_parameter(PID_Parameter_Index index)const {
    return ToPositionPD_linear_parameter_[index]; }
  void set_ToPositionPD_linear_parameter(double parameter,
                                         PID_Parameter_Index index) {
    ToPositionPD_linear_parameter_[index] = parameter; }
  double get_TurnToAngle_angular_parameter(PID_Parameter_Index index)const {
    return TurnToAngle_angular_parameter_[index]; }
  void set_TurnToAngle_angular_parameter(double parameter,
                                         PID_Parameter_Index index) {
    TurnToAngle_angular_parameter_[index] = parameter; }
 void LimitSpeed(double max_speed=ROBOT_INFO::WHEEL::MAX_SPEED);
 protected:
  
  
 private:
  enum { OLD_PID_DATA_NUM = 1 };
  enum { PID_PARAMETER_NUM = 3 };
  enum { NO_ACTION = 0, TO_POSITION_PD = 1, TURN_TO_ANGLE = 2 };

  void SetPIDParameter();
  void SaveParamToPositionPD();
  void SaveParamTurnToAngle();
  void ResetParamToPositionPD();
  void ResetParamTurnToAngle();
  
  // Update flag
  unsigned int update_mode;

  // PID parameter of ToPositionPD()
  double ToPositionPD_angular_parameter_[PID_PARAMETER_NUM];
  double ToPositionPD_linear_parameter_[PID_PARAMETER_NUM];
  // Current PID data of ToPositionPD()
  double ToPositionPD_angular_distance_;
  double ToPositionPD_linear_distance_;
  VecPosition ToPositionPD_target_;
  // Old PID data of ToPositionPD()
  double ToPositionPD_old_angular_distance_[OLD_PID_DATA_NUM];
  double ToPositionPD_old_linear_distance_[OLD_PID_DATA_NUM];
  VecPosition ToPositionPD_old_target_[OLD_PID_DATA_NUM];
  
  // PID parameter of TurnToAngle()
  double TurnToAngle_angular_parameter_[PID_PARAMETER_NUM];
  // Current PID data of TurnToAngle()
  double TurnToAngle_angular_distance_;
  // Old PID data of TurnToAngle()
  double TurnToAngle_old_angular_distance_[OLD_PID_DATA_NUM];
  
  // Disallow copy and assign
  void operator= (const RobotPID &) {}
};

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
      : RobotBasis(robotsimple.get_position(),
                   robotsimple.get_vector(),
                   robotsimple.get_theta()) {}
  virtual ~RobotSimple() {}

  void SightChase(const VecPosition &target);
  void Intercept(const Object &object);
  void PotentialFunction(const VecPosition &target);
};
class PowerRobot:public RobotPID{
};
class Robot:public RobotPID
{
public:
	void copyToRobotPID(){
		VecPosition newPos(pos.x,pos.y);
		this->Update(newPos,newPos-this->get_position(),rotation);
	}
	void copyToRobot(){
		velocityLeft=this->get_left_velocity();
		velocityRight=this->get_right_velocity();
	}
	Vector3D pos;											//机器人坐标 
	double rotation;										//机器人方向角 
	double velocityLeft, velocityRight;						//机器人左右轮速度 
	int index;
} ; 
class OpponentRobot:public RobotBasis{
public:
	void copyToRobotBasis(){
		VecPosition newPos(pos.x,pos.y);
		this->Update(newPos,newPos-this->get_position(),rotation);
	}
	Vector3D pos;											//机器人的坐标位置 
	double rotation;
};
/*class Ball:public BallBasis{
public:
	void copyToBallBasis(){
		VecPosition newPos(pos.x,pos.y);
		this->Update(newPos,newPos-this->get_position(),0);
	}
	Vector3D pos;	
};*/
#endif  // NEWNEU_ROBOT_SOCCER_09S_OBJECTS_H_