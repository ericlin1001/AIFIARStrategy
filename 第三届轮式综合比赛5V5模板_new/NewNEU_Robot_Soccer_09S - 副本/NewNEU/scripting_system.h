#ifndef NEWNEU_ROBOT_SOCCER_09S_SCRIPTINGSYSTEM_H_
#define NEWNEU_ROBOT_SOCCER_09S_SCRIPTINGSYSTEM_H_

#include <stdlib.h>
#include <stdio.h>

// By Code_B_Silence, NEU China
class ScriptingSystem {
 public:
  ScriptingSystem();
  explicit ScriptingSystem(char file_name[]);
  virtual ~ScriptingSystem() {}
  
  void SetFile(char file_name[]);
  double GetData(char search_string[]);

 private:
  enum { MAX_STRING_LENGTH = 64 };
  FILE *data_stream_;
  char file_name_[MAX_STRING_LENGTH];
  char input_string_[MAX_STRING_LENGTH];
  char copy_string_[MAX_STRING_LENGTH];
  char value_string_[MAX_STRING_LENGTH];
  double value_;
  
  // Disallow copy and assign
  ScriptingSystem(const ScriptingSystem &) {}
  void operator= (const ScriptingSystem &) {}
};

#endif  // NEWNEU_ROBOT_SOCCER_09S_SCRIPTINGSYSTEM_H_