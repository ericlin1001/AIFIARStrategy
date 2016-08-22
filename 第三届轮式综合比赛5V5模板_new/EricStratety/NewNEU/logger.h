#ifndef NEWNEU_ROBOT_SOCCER_09S_LOGGER_H_
#define NEWNEU_ROBOT_SOCCER_09S_LOGGER_H_

#include <stdio.h>
// By Code_B_Silence, NEU China
class Logger {
 public:
  Logger();
  virtual ~Logger();

  void SetWriteMode() { log_mode_ = WRITE; }
  void SetAddMode() { log_mode_ = ADD; }
  void OpenConsole();
  void OpenFile(char filename[]);
  void CloseConsole()const;
  void CloseFile()const;

  
  
  Logger & operator<< (char content[]);
  Logger & operator<< (double figure);
  Logger & operator<< (int integer);
  //
  int log_mode()const { return log_mode_; }
  bool console_is_opened()const { return console_is_opened_; }
  bool file_is_opened()const { return file_is_opened_; }

 private:
  enum { WRITE = 0, ADD = 1 };
  int log_mode_;
  bool console_is_opened_;
  bool file_is_opened_;
  FILE *output_file_;
  
  // Disallow copy and assign
  Logger(const Logger &) {}
  void operator= (const Logger &) {}
};

#endif  // NEWNEU_ROBOT_SOCCER_09S_LOGGER_H_