#include "stdafx.h"
#include "objects.h"

#include <math.h>

// ---- ---- ---- ---- Class Object ---- ---- ---- ----
// Default constructor.
Object::Object() {
  position_.SetVecPosition(0, 0);
  vector_.SetVecPosition(0, 0);
  theta_ = 0.0;
}

// Constructor. 
Object::Object(const VecPosition & position, const VecPosition & vec, double theta) {
  position_ = position;
  vector_ = vec;
  theta_ = theta;
}

// Overloaded version of the constructor.
Object::Object(const Object &object) {
  position_ = object.get_position();
  vector_ = object.get_vector();
  theta_ = object.get_theta();
}
// ---- ---- ---- ---- Class Object ---- ---- ---- ----

// ---- ---- ---- ---- Class BallBasis ---- ---- ---- ----
// Default constructor.
double BallBasis::ball_size_=DEFAULT_BALL_SIZE;
BallBasis::BallBasis() : Object() {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
  }
}
// Constructor. 
BallBasis::BallBasis(const VecPosition &position,
                     const VecPosition &vec, 
                     double theta) : Object(position, vec, theta) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
  }
  ball_size_ = DEFAULT_BALL_SIZE;
}

// Overloaded version of the constructor. 
BallBasis::BallBasis(const Object &object) : Object(object) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
  }
  ball_size_ = DEFAULT_BALL_SIZE;
}

// Overloaded version of the constructor. 
BallBasis::BallBasis(const BallBasis &ballbasis) 
    : Object(ballbasis.get_position(), ballbasis.get_vector(), 
             ballbasis.get_theta()) {
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
  }
  ball_size_ = ballbasis.get_ball_size();     
}

// Update ball information.
void BallBasis::Update(const VecPosition &position, 
                       const VecPosition &vec, 
                       double theta) {
  // Save old information.
  for (int i = 0; i < OLD_DATA_NUM - 1; ++i) {
    old_position_[i + 1] = old_position_[i];
    old_vector_[i + 1] = old_vector_[i];
    old_theta_[i + 1] = old_theta_[i];
  }
  old_position_[0] = get_position();
  old_vector_[0] = get_vector();
  old_theta_[0] = get_theta();

  // Update current information
  set_position(position);
  set_vector(vec);
  set_theta(theta);
}
// ---- ---- ---- ---- Class BallBasis ---- ---- ---- ----

// ---- ---- ---- ---- Class RobotBasis ---- ---- ---- ----
// Default constructor.
//static varibales:
double RobotBasis::robot_size_=DEFAULT_ROBOT_SIZE;
double RobotBasis::speed_limit_=DEFAULT_ROBOT_SPEED_LIMIT;
RobotBasis::RobotBasis() : Object() {
  left_velocity_ = 0.0;
  right_velocity_ = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
    old_left_velocity_[i] = 0.0;
    old_right_velocity_[i] = 0.0;
  } 
}
// Constructor. 
RobotBasis::RobotBasis(const VecPosition &position, 
                       const VecPosition &vec, 
                       double theta) : Object(position, vec, theta) {
  left_velocity_ = 0.0;
  right_velocity_ = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
    old_left_velocity_[i] = 0.0;
    old_right_velocity_[i] = 0.0;
  }
  robot_size_ = DEFAULT_ROBOT_SIZE;
  speed_limit_ = DEFAULT_ROBOT_SPEED_LIMIT;
}

// Overloaded version of the constructor.
RobotBasis::RobotBasis(const Object &object) : Object(object) {
  left_velocity_ = 0.0;
  right_velocity_ = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
    old_left_velocity_[i] = 0.0;
    old_right_velocity_[i] = 0.0;
  }
  robot_size_ = DEFAULT_ROBOT_SIZE;
  speed_limit_ = DEFAULT_ROBOT_SPEED_LIMIT;
}

// Overloaded version of the constructor.
RobotBasis::RobotBasis(const RobotBasis &robotbasis)
    : Object(robotbasis.get_position(), robotbasis.get_vector(),
             robotbasis.get_theta()) {
  left_velocity_ = 0.0;
  right_velocity_ = 0.0;
  for(int i = 0; i < OLD_DATA_NUM; ++i) {
    old_position_[i].SetVecPosition(0.0, 0.0);
    old_vector_[i].SetVecPosition(0.0, 0.0);
    old_theta_[i] = 0.0;
    old_left_velocity_[i] = 0.0;
    old_right_velocity_[i] = 0.0;
  }
  robot_size_ = robotbasis.get_robot_size();
  speed_limit_ = robotbasis.get_speed_limit();
}

// Update robot information.
void RobotBasis::Update(const VecPosition &position, 
                        const VecPosition &vec, 
                        double theta) {
  // Save old information.
  for (int i = OLD_DATA_NUM-2; i >=0; --i) {
    old_position_[i  + 1] = old_position_[i];
    old_vector_[i + 1] = old_vector_[i];
    old_theta_[i + 1] = old_theta_[i];
    old_left_velocity_[i + 1] = old_left_velocity_[i];
    old_right_velocity_[i + 1] = old_right_velocity_[i];
  }
  old_position_[0] = get_position();
  old_vector_[0] = get_vector();
  old_theta_[0] = get_theta();
  old_left_velocity_[0] = get_left_velocity();
  old_right_velocity_[0] = get_right_velocity();

  // Update current information.
  set_position(position);
  set_vector(vec);
  set_theta(theta);
  left_velocity_ = 0.0;
  right_velocity_ = 0.0;
  //TO DO:to set the velocity
}
// ---- ---- ---- ---- Class RobotBasis ---- ---- ---- ----

// ---- ---- ---- ---- Class RobotPID ---- ---- ---- ----
// Default constructor.
RobotPID::RobotPID() : RobotBasis() {
  SetPIDParameter();
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
    : RobotBasis(robotPID.get_position(), 
                 robotPID.get_vector(),
                 robotPID.get_theta()) {
  SetPIDParameter();
}

// Update robot information
void RobotPID::Update(const VecPosition &position,const VecPosition &vec,double theta) {
  switch (update_mode) {
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
  RobotBasis::Update(position, vec, theta);
  update_mode = NO_ACTION;
}

// Use PID method to control robots to the very point
void RobotPID::ToPositionPD(VecPosition target, double speed) {
  // Set update flag
  update_mode = TO_POSITION_PD;

  // Reset parameters if the target changed
  ToPositionPD_target_ = target;
  if (ToPositionPD_target_.GetDistanceTo(ToPositionPD_old_target_[0]) > 10) {
    ResetParamToPositionPD();//init the param
  }
  
  // Get the distance between robot and target
  VecPosition pos_relative = ToPositionPD_target_ - get_position();
  ToPositionPD_angular_distance_ = VecPosition::NormalizeAngle(
      pos_relative.GetDirection() - get_theta());
  
  ToPositionPD_linear_distance_ = pos_relative.GetX() * cos(get_theta())
      + pos_relative.GetY() * sin(get_theta());
      
  // If target is behind the robot, set the mark
  bool backward = false;
  if (fabs(ToPositionPD_angular_distance_) > PI / 2) {
    backward = true;
    ToPositionPD_angular_distance_ =
        (PI - fabs(ToPositionPD_angular_distance_))
        * Maths::Sign(ToPositionPD_angular_distance_);
  }
  
  // Calculate speed
  double angular_speed =
      ToPositionPD_angular_parameter_[P] *
      ToPositionPD_angular_distance_ +
      ToPositionPD_angular_parameter_[D] *
      (ToPositionPD_angular_distance_ - ToPositionPD_old_angular_distance_[0]);
  double linear_speed =
      ToPositionPD_linear_parameter_[P] *
      ToPositionPD_linear_distance_ +
      ToPositionPD_linear_parameter_[D] *
      (ToPositionPD_linear_distance_ - ToPositionPD_old_linear_distance_[0]);

  // Limit speed
  if (fabs(linear_speed) > speed) {
    linear_speed = speed * Maths::Sign(linear_speed);
  }
  
  // Adjust the linear speed according to angular distance
  linear_speed =
      linear_speed * exp(-1 * 1.5 * fabs(ToPositionPD_angular_distance_));

  // Set robot speed to 0 if it's close to target, to make a steady stop
  if (target.GetDistanceTo(get_position()) < 1) {
    angular_speed = 0;
    linear_speed = 0;
  }
  
  // Set the velocities of wheels
  if (backward) {
    angular_speed *= -1;
  }
  /*set_left_velocity(linear_speed - get_robot_size() * angular_speed);
  set_right_velocity(linear_speed + get_robot_size() * angular_speed);
  
  LimitSpeed(get_speed_limit());*/
  setDesiredSpeed(linear_speed,angular_speed);
}

// Use PID method to control robots turn to one direction
void RobotPID::TurnToAngle(double direction) {
  // Set update flag
  update_mode = TURN_TO_ANGLE;

  TurnToAngle_angular_direction_=direction;
  if (fabs(TurnToAngle_angular_direction_-TurnToAngle_old_angular_direction_[0])>0.001) {
    ResetParamTurnToAngle();//init the param
  }

  // Get angular distance
  TurnToAngle_angular_distance_ = VecPosition::NormalizeAngle(direction - get_theta());
  
  // Decide which side to turn
  bool turn_back = false;
  if (fabs(TurnToAngle_angular_distance_) > PI / 2) {
    turn_back = true;
    TurnToAngle_angular_distance_ = (PI - fabs(TurnToAngle_angular_distance_)) *Maths::Sign(TurnToAngle_angular_distance_);
  }
  
  // Calculate proper angular speed
  double angular_speed = 
      TurnToAngle_angular_parameter_[P] * 
      TurnToAngle_angular_distance_ +
      TurnToAngle_angular_parameter_[D] * 
      (TurnToAngle_angular_distance_ - TurnToAngle_old_angular_distance_[0]);

  // Set the wheels velocities      
  if (turn_back) {
    angular_speed *= -1;
  }
  setDesiredSpeed(0,angular_speed);
  /*
  set_left_velocity(-ROBOT_LENGTH * angular_speed);
  set_right_velocity(ROBOT_LENGTH * angular_speed);
  LimitSpeed(MAX_SPEED); */                  
}

// Limit the max speed of wheels, to make
// robots action steady.
void RobotPID::LimitSpeed(double max_speed) {
  double left_velocity = get_left_velocity();
  double right_velocity = get_right_velocity();

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
		set_left_velocity(max_speed*sign);
		set_right_velocity((max_speed - errand)*sign);
    }/*
    else if (left_velocity < -max_speed) {
      set_left_velocity(-max_speed);
      set_right_velocity(-max_speed + errand);
    }*/
  }else {
    if (fabs(right_velocity) > max_speed) {
		sign=Maths::Sign(right_velocity);
      set_right_velocity(max_speed*sign);
      set_left_velocity((max_speed - errand)*sign);
    }/*
    else if (right_velocity < -max_speed) {
      set_right_velocity(-max_speed);
      set_left_velocity(-max_speed + errand);
    }*/
  }
}

// Set PID method parameters.
void RobotPID::SetPIDParameter() {
  ToPositionPD_angular_parameter_[P] = 2.22;
  ToPositionPD_angular_parameter_[I] = 0.0;
  ToPositionPD_angular_parameter_[D] = 3.28;

  ToPositionPD_linear_parameter_[P] = 2.5;
  ToPositionPD_linear_parameter_[I] = 0.0;
  ToPositionPD_linear_parameter_[D] = 7.8;
  
  TurnToAngle_angular_parameter_[P] = 3.5;
  TurnToAngle_angular_parameter_[I] = 0.0;
  TurnToAngle_angular_parameter_[D] = 0.5;
}

// Save the old ToPositionPD() parameters.
void RobotPID::SaveParamToPositionPD() {
  for (int i = OLD_PID_DATA_NUM-2; i >=0; --i) {
    ToPositionPD_old_angular_distance_[i + 1] 
        = ToPositionPD_old_angular_distance_[i];
    ToPositionPD_old_linear_distance_[i + 1]
        = ToPositionPD_old_linear_distance_[i];
    ToPositionPD_old_target_[i + 1]
        = ToPositionPD_old_target_[i];
  }
  ToPositionPD_old_angular_distance_[0] = ToPositionPD_angular_distance_;
  ToPositionPD_old_linear_distance_[0] = ToPositionPD_linear_distance_;
  ToPositionPD_old_target_[0] = ToPositionPD_target_;
}

// Save the old TurnToAngle() parameters.
void RobotPID::SaveParamTurnToAngle() {
  for (int i = OLD_PID_DATA_NUM-2; i >=0; --i) {
    TurnToAngle_old_angular_distance_[i + 1]
        = TurnToAngle_old_angular_distance_[i];
	TurnToAngle_old_angular_direction_[i+1]=
		TurnToAngle_old_angular_direction_[i];
  }
  TurnToAngle_old_angular_distance_[0] = TurnToAngle_angular_distance_;
  TurnToAngle_old_angular_direction_[0]=TurnToAngle_angular_direction_;
}

// Reset ToPositionPD() parameters.
void RobotPID::ResetParamToPositionPD() {
  for (int i = 0; i < OLD_PID_DATA_NUM; ++i) {
    ToPositionPD_old_angular_distance_[i] = 0.0;
    ToPositionPD_old_linear_distance_[i] = 0.0;
    ToPositionPD_old_target_[i].SetVecPosition(0, 0);
  }
}

// Reset TurnToAngle() parameters.
void RobotPID::ResetParamTurnToAngle() {
  for (int i = 0; i < OLD_PID_DATA_NUM; ++i) {
    TurnToAngle_old_angular_distance_[i] = 0.0;
	TurnToAngle_old_angular_direction_[i]=0.0;
  }
}
// ---- ---- ---- ---- Class RobotPID ---- ---- ---- ----

// ---- ---- ---- ---- Class RobotSimple ---- ---- ---- ----
void RobotSimple::SightChase(const VecPosition &target) {
  // Adjust wheels speed base on different situation
  // parameter "target" is const, can't call GlobalToRelative()
  // make a copy here
  VecPosition temp_target = target;
  temp_target.GlobalToRelative(Object::get_position(), Object::get_theta());
  if (temp_target.GetY() > 0.05) {
    RobotBasis::set_left_velocity(60);
    RobotBasis::set_right_velocity(70);
  }
  else if (temp_target.GetY() < -0.05) {
    RobotBasis::set_left_velocity(70);
    RobotBasis::set_right_velocity(60);  
  }
  else {
    RobotBasis::set_left_velocity(80);
    RobotBasis::set_right_velocity(80);  
  }
  // Decide action direction
  if (temp_target.GetX() < 0) {
    RobotBasis::set_left_velocity(-RobotBasis::get_left_velocity());
    RobotBasis::set_right_velocity(-RobotBasis::get_right_velocity());
  }
}

void RobotSimple::Intercept(const Object &object) {
  // TODO: Add comments
  VecPosition vr, sr, st;
  double tc;
  
  VecPosition object_position = object.get_position();
  VecPosition object_vec = object.get_vector();
  vr = object_vec - Object::get_vector();
  sr.SetVecPosition(
      object_position.GetX() - Object::get_position().GetX(),
      object_position.GetY() - Object::get_position().GetY());
  tc = sr.GetMagnitude() / vr.GetMagnitude();
  st.SetVecPosition(
      object_position.GetX() + (object_vec.GetX() * tc),
      object_position.GetY() + (object_vec.GetY() * tc));

  SightChase(st);
}

void RobotSimple::PotentialFunction(const VecPosition &target) {
  // TODO: Add comments
  VecPosition temp_target(target);
  VecPosition temp_position(Object::get_position());
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