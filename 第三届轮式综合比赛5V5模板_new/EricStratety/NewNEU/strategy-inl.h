#ifndef NEWNEU_ROBOT_SOCCER_09S_STRATEGY_INL_H_
#define NEWNEU_ROBOT_SOCCER_09S_STRATEGY_INL_H_

inline bool StrategyBasis::set_ball(const BallBasis ball) {
  ball_.Update(ball.get_position(), ball.get_vector(), ball.get_theta());
  return true;
}

inline bool StrategyBasis::set_robot(const RobotBasis robot, int index) {
  if (index < ROBOT_NUMBER) {
    robots_[index].Update(robot.get_position(), 
                          robot.get_vector(), 
                          robot.get_theta());
  }
  else {
    // Set new data fail, index overflow
    return false;
  }
  return true;
}

inline bool StrategyBasis::set_opponent(const RobotBasis opponent, int index) {
  if (index < ROBOT_NUMBER) {
    opponents_[index].Update(opponent.get_position(),
                             opponent.get_vector(),
                             opponent.get_theta());
  }
  else {
    // Set new data fail, index overflow
    return false;
  }
  return true;
}

#endif  // NEWNEU_ROBOT_SOCCER_09S_STRATEGY_INL_H_