#include "stdafx.h"
#include "logger.h"

// ---- ---- ---- ---- Class Logger ---- ---- ---- -----
// Constructor of class CLog. The output is set to be WRITE mode by default. 
Logger::Logger() {
  log_mode_ = WRITE;
  console_is_opened_ = false;
  file_is_opened_ = false;
}

// If the console, in another case the file, is not close, close it. 
// If other processes share the console, the console is not destroyed, but 
// the calling process cannot refer to it.
Logger::~Logger() {
  if (console_is_opened_) {
    CloseConsole();
  }
  if (file_is_opened_) {
    CloseFile();
  }
}

// Open the console and set the mark m_bConsoleOpened true.
void Logger::OpenConsole() {
  AllocConsole();
  switch (log_mode_) {
    case WRITE: {
      if (!freopen_s(&output_file_, "CONOUT$", "w+t", stdout)) {
        console_is_opened_ = true;
        }
        break;
      }
    case ADD: {
      if (!freopen_s(&output_file_, "CONOUT$", "a+t", stdout)) {
        console_is_opened_ = true;
        }
        break;
      }
    default:
      break;
  }
}

// Open the file and set the mark m_bFileOpened true. 
void Logger::OpenFile(const char filename[]) {
  AllocConsole();
  switch (log_mode_) {
    case WRITE: {
      if (!fopen_s(&output_file_, filename, "w+t")) {
        file_is_opened_ = true;
        }
        break;
      }
    case ADD: {
      if (!fopen_s(&output_file_, filename, "a+t")) {
        file_is_opened_ = true;
        }
        break;
      }
    default:
      break;
  }
}

// Close the console. If other processes share the console, the console 
// is not destroyed, but the calling process cannot refer to it.
void Logger::CloseConsole()const {
  FreeConsole();
}

// Close the file.
void Logger::CloseFile()const {
  if (output_file_ != NULL) {
    fclose(output_file_);
  }	
}

// Overload operator <<. Output a string to either console or file if possible.
Logger & Logger::operator<< (char content[]) {
  if (console_is_opened_ || file_is_opened_) {
    fputs(content, output_file_);
  }
  return *this;
}

// Overload operator <<.
Logger & Logger::operator<< (double figure) {
  if (console_is_opened_ || file_is_opened_) {
    fprintf(output_file_, "%f", figure);
  }
  return *this;
}

// Overload operator <<.
Logger & Logger::operator<< (int integer) {
  if (console_is_opened_ || file_is_opened_) {
    fprintf(output_file_, "%d", integer);
  }
  return *this;
}
// ---- ---- ---- ---- Class CLog ---- ---- ---- -----
