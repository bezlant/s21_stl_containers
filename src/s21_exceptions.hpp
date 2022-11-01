#ifndef S21_EXCEPTIONS_H_
#define S21_EXCEPTIONS_H_
#include <iostream>

class ZeroSizeException : public std::exception {
  private:
    std::string message =
        "Use methods on a zero sized container results in the UB";

  public:
    const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif  // S21_EXCEPTIONS_H_
