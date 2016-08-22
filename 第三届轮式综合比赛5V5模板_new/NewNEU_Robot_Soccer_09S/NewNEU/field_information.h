#ifndef NEWNEU_ROBOT_SOCCER_09S_FIELD_INFORMATION_H_
#define NEWNEU_ROBOT_SOCCER_09S_FIELD_INFORMATION_H_
#include "GeometryR.h"
class FieldInformationBasis {
public:
	FieldInformationBasis();
	virtual ~FieldInformationBasis() {}
	VecPosition get_field_vec()const{return VecPosition(this->get_field_length(),this->get_field_width());}
	static double get_field_length()const { return field_length_; }
	static double get_field_width()const { return field_width_; }
	static double get_penalty_area_length()const { return penalty_area_length_; }
	static double get_penalty_area_width()const { return penalty_area_width_; }
	static double get_goal_area_length()const { return goal_area_length_; }
	static double get_goal_area_width()const { return goal_area_width_; }
	static double get_goal_length()const { return goal_length_; }
	static double get_goal_width()const { return goal_width_; }
	//// Temporarily, and maybe ever, not used match state information
	enum Area{ LEFT= 0, RIGHT = 1 };
	enum Ball_Ownership{ ANYONE = 0, BULL_TEAM = 1, YELLOW_TEAM = 2 };
	enum Match_State{ NORMAL = 0, FREE_BALL = 1, PENALTY_KICK = 2,
	                 FREE_KICK = 3, GOAL_KICK = 4, UNDER_WAY = 5 };
	enum Penalty_State{ DEFENSE = 0, ATTACK = 1 };
	//
private:
	void set_field_length(double length) { field_length_ = length; }
	static void set_field_width(double width) { field_width_ = width; }
	static void set_penalty_area_length(double length) {  penalty_area_length_ = length; }
	static void set_penalty_area_width(double width) { penalty_area_width_ = width; }
	static void set_goal_area_length(double length) { goal_area_length_ = length; }
	static void set_goal_area_width(double width) { goal_area_width_ = width; }
	static void set_goal_length(double length) { goal_length_ = length; }
	static void set_goal_width(double width) { goal_width_ = width; }
private:
	

	static double field_length_;
	static double field_width_;
	static double penalty_area_length_;
	static double penalty_area_width_;
	static double goal_area_length_;
	static double goal_area_width_;
	static double goal_length_;
	static double goal_width_;

	// Disallow copy and assign
	FieldInformationBasis(const FieldInformationBasis &) {}
	void operator= (const FieldInformationBasis &) {}
};
class FieldInfo:public FieldInformationBasis{
public:
	FieldInfo(){}
};
#endif  // NEWNEU_ROBOT_SOCCER_09S_FIELD_INFORMATION_H_