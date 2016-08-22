#include "stdafx.h"
#include "scripting_system.h"

// ---- ---- ---- ---- Class ScriptingSystem ---- ---- ---- ----
// Default constructor.
ScriptingSystem::ScriptingSystem() {
  file_name_[0] = '\0';
}
// Constructor. 
ScriptingSystem::ScriptingSystem(char file_name[]) {
  SetFile(file_name);
}

// Set the file's path.
void ScriptingSystem::SetFile(char file_name[]) {
  strncpy_s(file_name_, MAX_STRING_LENGTH, file_name, _TRUNCATE);
}

// Get data by searching the given word in the loaded file.
double ScriptingSystem::GetData(char search_string[]) {
  // Open the file in read mode
  int i, j;	
  fopen_s(&data_stream_, file_name_, "r");
  if (data_stream_ != NULL) {
    while (!feof(data_stream_)) {
      // Get a line and store in input_string_
      if (!fgets(input_string_, MAX_STRING_LENGTH, data_stream_)) {
        fclose(data_stream_);
        return 0;
      }
      j = 0;
      // Empty copy_string_
      strcpy_s(copy_string_, MAX_STRING_LENGTH, "");
      // Copy the input_string_ to copy_string_, throw off all the blanks
      for (i = 0; i < (int)strlen(input_string_); i++) {
        if (input_string_[i] != ' ') {
          copy_string_[j] = input_string_[i];
          copy_string_[j + 1] = '\0';
          j++;
        }
      }
      // Find the search word
      if (strncmp(search_string, copy_string_, strlen(search_string)) == 0) {
        j = 0;
        // Copy the string follow the search word to value_string_
        for (i = strlen(search_string); i < MAX_STRING_LENGTH; i++) {
          if (copy_string_[i] == ';') {
            break;
          }
        value_string_[j] = copy_string_[i];
        value_string_[j + 1] = '\0';
        j++;
        }
        // Convert the figure in value_string_ to number, and store in value_
        value_ = atof(value_string_);
        fclose(data_stream_);
        // Return result int double type
        return value_;
      }
    }
    fclose(data_stream_);
    return 0;
  }
  return 0;
}

// ---- ---- ---- ---- Class ScriptingSystem ---- ---- ---- ----
