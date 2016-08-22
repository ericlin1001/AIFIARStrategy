#include "stdafx.h"
#include "field_information.h"
#include "defines.h"

// ---- ---- ---- ---- Class FieldInformationBasis ---- ---- ---- ----
// Default constructor.
FieldInformationBasis::FieldInformationBasis() {
  // 5 versus 5 field information
  field_length_ = PITCH_LENGTH;
  field_width_ = PITCH_WIDTH;
  penalty_area_length_ = PENALTY_AREA_LENGTH;
  penalty_area_width_ = PENALTY_AREA_WIDTH;
  goal_area_length_ = GOAL_AREA_LENGTH;
  goal_area_width_ = GOAL_AREA_WIDTH;
  goal_length_ = GOAL_DEPTH;
  goal_width_ = GOAL_WIDTH;
};