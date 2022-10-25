#ifndef S21_EXCEPTIONS_H_
#define S21_EXCEPTIONS_H_
#include <iostream>

class FrontBackUbException : public std::exception {
  private:
    std::string message =
        "Calling front or back on empty containers results in UB";

  public:
    const char *what() const noexcept override {
        return message.c_str();
    }
};
#endif  // S21_EXCEPTIONS_H_
