#include "stdafx.h"
#include "objects.h"

#include <math.h>

// ---- ---- ---- ---- Class Object ---- ---- ---- ----
// Default constructor.
Object::Object() {
  reset();
}
void Object::reset(){
  _position.SetVecPosition(0, 0);
  _vector.SetVecPosition(0, 0);
  _theta = 0.0;
}
// Constructor. 
Object::Object(const VecPosition & position, const VecPosition & vec, double theta) {
  this->_position = position;
  this->_vector = vec;
  this->_theta = theta;
}

// Overloaded version of the constructor.
Object::Object(const Object &object) {
  _position = object.getPosition();
  _vector = object.getVector();
  _theta = object.getTheta();
}
// ---- ---- ---- ---- Class Object ---- ---- ---- ----

// ---- ---- ---- ---- Class BallBasis ---- ---- ---- ----
// Default constructor.
//double BallBasis::ball_size_=DEFAULT_BALL_SIZE;
BallBasis::BallBasis() : Object() {
  reset();
}
void BallBasis::reset(){
	for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
  }
}
// Constructor. 
BallBasis::BallBasis(const VecPosition &position,
                     const VecPosition &vec, 
                     double theta) : Object(position, vec, theta) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
  }
}

// Overloaded version of the constructor. 
BallBasis::BallBasis(const Object &object) : Object(object) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
  }
}

// Overloaded version of the constructor. 
BallBasis::BallBasis(const BallBasis &ballbasis) 
    : Object(ballbasis.getPosition(), ballbasis.getVector(), 
             ballbasis.getTheta()) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
  }    
}

// Update ball information.
void BallBasis::Update(const VecPosition &position, 
                       double theta) {
  // Save old information.
  for (int i = 0; i < OLD_DATA_NUM - 1; ++i) {
    oldPosition[i + 1] = oldPosition[i];
    oldVector[i + 1] = oldVector[i];
    oldTheta[i + 1] = oldTheta[i];
  }
  oldPosition[0] = getPosition();
  oldVector[0] = getVector();
  oldTheta[0] = getTheta();

  // Update current information
  setPosition(position);
  setVector(position-oldPosition[0]);
  setTheta(theta);
}
// ---- ---- ---- ---- Class BallBasis ---- ---- ---- ----

// ---- ---- ---- ---- Class RobotBasis ---- ---- ---- ----
// Default constructor.
//static varibales:
/*double RobotBasis::robot_size_=DEFAULT_ROBOT_SIZE;
double RobotBasis::speed_limit_=DEFAULT_ROBOT_SPEED_LIMIT;
*/
RobotBasis::RobotBasis() : Object() {
 reset();
}
void RobotBasis::reset(){
	leftVelocity = 0.0;
  rightVelocity = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
    oldLeftVelocity[i] = 0.0;
    oldRightVelocity[i] = 0.0;
  } 
}
// Limit the max speed of wheels, to make
// robots action steady.
void RobotBasis::LimitSpeed(double max_speed) {
  double left_velocity = getLeftVelocity();
  double right_velocity = getRightVelocity();

  double errand = fabs(left_velocity - right_velocity);

  if (errand > 2 * max_speed) {
    errand = 2 * max_speed;
  }
  //below script guarantee the angular speed not changed,but linear speed is deceased.
  //robot:l->r , linear speed=(l+r)/2,angular speed=(r-l)/2;
  int sign;
  if (fabs(left_velocity) > fabs(right_velocity)) {
    if (fabs(left_velocity) > max_speed) {
		sign=Maths::Sign(left_velocity);
		setLeftVelocity(max_speed*sign);
		setRightVelocity((max_speed - errand)*sign);
    }/*
    else if (left_velocity < -max_speed) {
      setLeftVelocity(-max_speed);
      setRightVelocity(-max_speed + errand);
    }*/
  }else {
    if (fabs(right_velocity) > max_speed) {
		sign=Maths::Sign(right_velocity);
      setRightVelocity(max_speed*sign);
      setLeftVelocity((max_speed - errand)*sign);
    }/*
    else if (right_velocity < -max_speed) {
      setRightVelocity(-max_speed);
      setLeftVelocity(-max_speed + errand);
    }*/
  }
}

// Constructor. 
RobotBasis::RobotBasis(const VecPosition &position, 
                       const VecPosition &vec, 
                       double theta) : Object(position, vec, theta) {
  leftVelocity = 0.0;
  rightVelocity = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
    oldLeftVelocity[i] = 0.0;
    oldRightVelocity[i] = 0.0;
  }
}

// Overloaded version of the constructor.
RobotBasis::RobotBasis(const Object &object) : Object(object) {
  leftVelocity = 0.0;
  rightVelocity = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
    oldLeftVelocity[i] = 0.0;
    oldRightVelocity[i] = 0.0;
  }
}

// Overloaded version of the constructor.
RobotBasis::RobotBasis(const RobotBasis &robotbasis)
    : Object(robotbasis.getPosition(), robotbasis.getVector(),
             robotbasis.getTheta()) {
  leftVelocity = 0.0;
  rightVelocity = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    oldPosition[i].SetVecPosition(0.0, 0.0);
    oldVector[i].SetVecPosition(0.0, 0.0);
    oldTheta[i] = 0.0;
    oldLeftVelocity[i] = 0.0;
    oldRightVelocity[i] = 0.0;
  }
}

// Update robot information.
void RobotBasis::Update(const VecPosition &position, 
                        double theta) {
  // Save old information.
  for (int i = OLD_DATA_NUM-2; i >=0; --i) {
    oldPosition[i  + 1] = oldPosition[i];
    oldVector[i + 1] = oldVector[i];
    oldTheta[i + 1] = oldTheta[i];
    oldLeftVelocity[i + 1] = oldLeftVelocity[i];
    oldRightVelocity[i + 1] = oldRightVelocity[i];
  }
  oldPosition[0] = getPosition();
  oldVector[0] = getVector();
  oldTheta[0] = getTheta();
  oldLeftVelocity[0] = getLeftVelocity();
  oldRightVelocity[0] = getRightVelocity();

  // Update current information.
  setPosition(position);
  setVector(position-oldPosition[0]);
  setTheta(theta);
  leftVelocity = 0.0;
  rightVelocity = 0.0;
  //TO DO:to set the velocity
}
// ---- ---- ---- ---- Class RobotBasis ---- ---- ---- ----

// ---- ---- ---- ---- Class RobotPID ---- ---- ---- ----
// Default constructor.
RobotPID::RobotPID() : RobotBasis() {
  reset();
}
void RobotPID::reset(){
	SetPIDParameter();
	 ResetParamToPositionPD();
	 ResetParamTurnToAngle();
}
// Constructor.
RobotPID::RobotPID(const VecPosition &position, 
                   const VecPosition &vec, 
                   double theta) : RobotBasis(position, vec, theta) {
  SetPIDParameter();                  
}

// Overloaded version of the constructor.
RobotPID::RobotPID(const Object &object)
    : RobotBasis(object) {
  SetPIDParameter();
}

// Overloaded version of the constructor.
RobotPID::RobotPID(const RobotBasis &robotbasis)
    : RobotBasis(robotbasis) {
  SetPIDParameter();
}

// Overloaded version of the constructor.
RobotPID::RobotPID(const RobotPID &robotPID) 
    : RobotBasis(robotPID.getPosition(), 
                 robotPID.getVector(),
                 robotPID.getTheta()) {
  SetPIDParameter();
}

// Update robot information
void RobotPID::Update(const VecPosition &position,double theta) {
  switch (updateMode) {
    case NO_ACTION: {
      ResetParamToPositionPD();
      ResetParamTurnToAngle();
      break;
      }
    case TO_POSITION_PD: {
      SaveParamToPositionPD();
      //ResetParamTurnToAngle();
      break;
      }
    case TURN_TO_ANGLE: {
      SaveParamTurnToAngle();
      //ResetParamToPositionPD();
      break;
      }
    default:
      break;
  }
  RobotBasis::Update(position, theta);
  updateMode = NO_ACTION;
}

// Use PID method to control robots to the very point
void RobotPID::ToPositionPD(VecPosition target, double speed) {
  // Set update flag
  updateMode = TO_POSITION_PD;

  // Reset parameters if the target changed
  ToPositionPDTarget = target;
  if (ToPositionPDTarget.GetDistanceTo(ToPositionPDOldTarget[0]) > 10) {
    ResetParamToPositionPD();//init the param
  }
  
  // Get the distance between robot and target
  VecPosition pos_relative = ToPositionPDTarget - getPosition();
  ToPositionPDAngularDistance = VecPosition::NormalizeAngle(
      pos_relative.GetDirection() - getTheta());
  
  ToPositionPDLinearDistance = pos_relative.GetX() * cos(getTheta())
      + pos_relative.GetY() * sin(getTheta());
      
  // If target is behind the robot, set the mark
  bool backward = false;
  if (fabs(ToPositionPDAngularDistance) > PI / 2) {
    backward = true;
    ToPositionPDAngularDistance =
        (PI - fabs(ToPositionPDAngularDistance))
        * Maths::Sign(ToPositionPDAngularDistance);
  }
  
  // Calculate speed
  double angular_speed =
      ToPositionPDAngularParameter[P] *
      ToPositionPDAngularDistance +
      ToPositionPDAngularParameter[D] *
      (ToPositionPDAngularDistance - ToPositionPDOldAngularDistance[0]);
  double linear_speed =
      ToPositionPDLinearParameter[P] *
      ToPositionPDLinearDistance +
      ToPositionPDLinearParameter[D] *
      (ToPositionPDLinearDistance - ToPositionPDOldLinearDistance[0]);

  // Limit speed
  if (fabs(linear_speed) > speed) {
    linear_speed = speed * Maths::Sign(linear_speed);
  }
  
  // Adjust the linear speed according to angular distance
  linear_speed =
      linear_speed * exp(-1 * 1.5 * fabs(ToPositionPDAngularDistance));

  // Set robot speed to 0 if it's close to target, to make a steady stop
  if (target.GetDistanceTo(getPosition()) < 1) {
    angular_speed = 0;
    linear_speed = 0;
  }
  
  // Set the velocities of wheels
  if (backward) {
    angular_speed *= -1;
  }
  /*setLeftVelocity(linear_speed - get_robot_size() * angular_speed);
  setRightVelocity(linear_speed + get_robot_size() * angular_speed);
  
  LimitSpeed(get_speed_limit());*/
  setDesiredSpeed(linear_speed,angular_speed);
}

// Use PID method to control robots turn to one direction
void RobotPID::TurnToAngle(double direction) {
  // Set update flag
  updateMode = TURN_TO_ANGLE;

  TurnToAngleAngularDirection=direction;
  if (fabs(TurnToAngleAngularDirection-TurnToAngleOldAngularDirection[0])>0.001) {
    ResetParamTurnToAngle();//init the param
  }

  // Get angular distance
  TurnToAngleAngularDistance = VecPosition::NormalizeAngle(direction - getTheta());
  
  // Decide which side to turn
  bool turn_back = false;
  if (fabs(TurnToAngleAngularDistance) > PI / 2) {
    turn_back = true;
    TurnToAngleAngularDistance = (PI - fabs(TurnToAngleAngularDistance)) *Maths::Sign(TurnToAngleAngularDistance);
  }
  
  // Calculate proper angular speed
  double angular_speed = 
      TurnToAngleAngularParameter[P] * 
      TurnToAngleAngularDistance +
      TurnToAngleAngularParameter[D] * 
      (TurnToAngleAngularDistance - TurnToAngleOldAngularDistance[0]);

  // Set the wheels velocities      
  if (turn_back) {
    angular_speed *= -1;
  }
  setDesiredSpeed(0,angular_speed);
  /*
  setLeftVelocity(-ROBOT_LENGTH * angular_speed);
  setRightVelocity(ROBOT_LENGTH * angular_speed);
  LimitSpeed(MAX_SPEED); */                  
}



// Set PID method parameters.
void RobotPID::SetPIDParameter() {
  ToPositionPDAngularParameter[P] = 2.22;
  ToPositionPDAngularParameter[I] = 0.0;
  ToPositionPDAngularParameter[D] = 3.28;

  ToPositionPDLinearParameter[P] = 2.5;
  ToPositionPDLinearParameter[I] = 0.0;
  ToPositionPDLinearParameter[D] = 7.8;
  
  TurnToAngleAngularParameter[P] = 3.5;
  TurnToAngleAngularParameter[I] = 0.0;
  TurnToAngleAngularParameter[D] = 0.5;
}

// Save the old ToPositionPD() parameters.
void RobotPID::SaveParamToPositionPD() {
  for (int i = OLD_PID_DATA_NUM-2; i >=0; --i) {
    ToPositionPDOldAngularDistance[i + 1] 
        = ToPositionPDOldAngularDistance[i];
    ToPositionPDOldLinearDistance[i + 1]
        = ToPositionPDOldLinearDistance[i];
    ToPositionPDOldTarget[i + 1]
        = ToPositionPDOldTarget[i];
  }
  ToPositionPDOldAngularDistance[0] = ToPositionPDAngularDistance;
  ToPositionPDOldLinearDistance[0] = ToPositionPDLinearDistance;
  ToPositionPDOldTarget[0] = ToPositionPDTarget;
}

// Save the old TurnToAngle() parameters.
void RobotPID::SaveParamTurnToAngle() {
  for (int i = OLD_PID_DATA_NUM-2; i >=0; --i) {
    TurnToAngleOldAngularDistance[i + 1]
        = TurnToAngleOldAngularDistance[i];
	TurnToAngleOldAngularDirection[i+1]=
		TurnToAngleOldAngularDirection[i];
  }
  TurnToAngleOldAngularDistance[0] = TurnToAngleAngularDistance;
  TurnToAngleOldAngularDirection[0]=TurnToAngleAngularDirection;
}

// Reset ToPositionPD() parameters.
void RobotPID::ResetParamToPositionPD() {
  for (int i = 0; i < OLD_PID_DATA_NUM; ++i) {
    ToPositionPDOldAngularDistance[i] = 0.0;
    ToPositionPDOldLinearDistance[i] = 0.0;
    ToPositionPDOldTarget[i].SetVecPosition(0, 0);
  }
}

// Reset TurnToAngle() parameters.
void RobotPID::ResetParamTurnToAngle() {
  for (int i = 0; i < OLD_PID_DATA_NUM; ++i) {
    TurnToAngleOldAngularDistance[i] = 0.0;
	TurnToAngleOldAngularDirection[i]=0.0;
  }
}
// ---- ---- ---- ---- Class RobotPID ---- ---- ---- ----

/*
// ---- ---- ---- ---- Class RobotSimple ---- ---- ---- ----
void RobotSimple::SightChase(const VecPosition &target) {
  // Adjust wheels speed base on different situation
  // parameter "target" is const, can't call GlobalToRelative()
  // make a copy here
  VecPosition temp_target = target;
  temp_target.GlobalToRelative(Object::getPosition(), Object::getTheta());
  if (temp_target.GetY() > 0.05) {
    RobotBasis::setLeftVelocity(60);
    RobotBasis::setRightVelocity(70);
  }
  else if (temp_target.GetY() < -0.05) {
    RobotBasis::setLeftVelocity(70);
    RobotBasis::setRightVelocity(60);  
  }
  else {
    RobotBasis::setLeftVelocity(80);
    RobotBasis::setRightVelocity(80);  
  }
  // Decide action direction
  if (temp_target.GetX() < 0) {
    RobotBasis::setLeftVelocity(-RobotBasis::getLeftVelocity());
    RobotBasis::setRightVelocity(-RobotBasis::getRightVelocity());
  }
}

void RobotSimple::Intercept(const Object &object) {
  // TODO: Add comments
  VecPosition vr, sr, st;
  double tc;
  
  VecPosition object_position = object.getPosition();
  VecPosition object_vec = object.getVector();
  vr = object_vec - Object::getVector();
  sr.SetVecPosition(
      object_position.GetX() - Object::getPosition().GetX(),
      object_position.GetY() - Object::getPosition().GetY());
  tc = sr.GetMagnitude() / vr.GetMagnitude();
  st.SetVecPosition(
      object_position.GetX() + (object_vec.GetX() * tc),
      object_position.GetY() + (object_vec.GetY() * tc));

  SightChase(st);
}

void RobotSimple::PotentialFunction(const VecPosition &target) {
  // TODO: Add comments
  VecPosition temp_target(target);
  VecPosition temp_position(Object::getPosition());
  VecPosition r = temp_position - temp_target;
  VecPosition u = r;
  u.Normalize();
  
  double k, a, b, c, m, d;  // Function parameters
  a = 300;
  b = 500;
  c = 2;
  m = 3;
  d = r.GetMagnitude() / RobotBasis::get_robot_size();
  // Potential function: U = A/r^n + B/r^m 
  // if A > 0 and B < 0, robot evade the target; 
  // else if A < 0 and B > 0, robot chase it
  k = a / pow(d, c) - b / pow(d, m);

  temp_target = u * k;
  temp_target.RelativeToGlobal(temp_position, 0);
  SightChase(temp_target);
}
// ---- ---- ---- ---- Class RobotSimple ---- ---- ---- ----
*/

/*基本动作——Basic Actions, BA
		ToPostion 	到定点（停）
		TurnAngle	转动一定角度
		MoveAlong	向某点(或方向)作定向运动

技术动作——Skilled Actions, SA
		KickBall		    踢球动作
		ShootGoal	    射门
		TurnShoot	    转身射门
		DefenseBall	    防球（回防）
		BlockMan	    盯人防守
		AvoidBound	    防止碰撞边界

		KeepGoal 			守门员防守
		ProcessBoundBall 	边界球处理
		ProcessCornerBall 	角球处理
		PassBall2Pt 			传球到定点
		AvoidObst2Pt 		避障碍到定点

组合动作(单人)
              ——Combinatorial Action, CA
		PenaltyKick 		（罚点球）
		GoalKick	 		（罚门球）
		FreeBall			（争球）
		FreeKick 			（罚任意球）

战术动作(多人)
             ——Tactical Actions, TA   	
		NormalKickoff 			中场开球
		Pass2Shoot 			一传一射
		BL_Pass2CenterShoot 	底线传中射门

*/