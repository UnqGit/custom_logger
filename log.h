#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <print>
#include <format>
#include <string>
#include <concepts>
#include <stdexcept>

// Sugar file....beware of diabetes.

class Console;
class Exception;

extern Console &console;
extern Exception &error;

template <typename T>
requires std::floating_point<T> || std::integral<T>
std::string operator+(const std::string &str, T value) {return str + std::to_string(value);}

template <typename T>
requires std::floating_point<T> || std::integral<T>
std::string operator+(T value, const std::string &str) {return std::to_string(value) + str;}

class Console {
  private:
    Console() {}
    Console(const Console&) = delete;
    Console& operator=(const Console&) = delete;

  public:
    constexpr static Console& instance() {
      static Console instance;
      return instance;
    }

    Console& log(const auto &arg) { // Log to the console.
      std::cout << arg;
      return *this;
    }
    Console& logln() {
      std::cout << '\n';
      return *this;
    }
    Console& logln(const auto &arg) { // Log to the console with a newline character at the end.
      std::cout << arg << '\n';
      return *this;
    }

    Console& log(const auto &...Args) { // Logs multiple inputs without a space in between.
      ((std::cout << Args), ...);
      return *this;
    }
    Console& logln(const auto &...Args) {
      ((std::cout << Args), ...);
      std::cout << '\n';
      return *this;
    }

    Console& logs() {
      std::cout << ' ';
      return *this;
    }
    Console& logs(const auto &...Args) {
      ((std::cout << Args << ' '), ...);
      return *this;
    }
    Console& log_sln() {
      std::cout << " \n";
      return *this;
    }
    Console& log_sln(const auto &...Args) {
      ((std::cout << Args << ' '), ...);
      std::cout << '\n';
      return *this;
    }

    Console& log_mln(const auto &...Args) {
      ((std::cout << Args << '\n'), ...);
      return *this;
    }

    template <typename... Args>
    Console& logf(const std::format_string<Args...> &fmt, Args&&... args) {
      std::print(fmt, std::forward<Args>(args)...);
      return *this;
    }
    template <typename... Args>
    Console& log_fln(const std::format_string<Args...> &fmt, Args&&... args) {
      std::println(fmt, std::forward<Args>(args)...);
      return *this;
    }

    bool get(auto &variable) { // Gives true, if occured successfully.
      bool successful = (std::cin >> variable);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return successful;
    }

    bool getln(auto &variable) {
      return std::getline(std::cin, variable);
    }

    bool getm(auto &...Args) {
      bool successful = true;
      successful &= (bool)((std::cin >> Args), ...);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return successful;
    }

    Console& clog(const auto &...Args) {
      ((std::cerr << Args), ...);
      return *this;
    }

    Console& pause(const std::string &pause_message = "");
    Console& pause(size_t seconds, const std::string &pause_message = "");
    Console& pause(float seconds, const std::string &pause_message = "");
    Console& pause_ms(size_t milliseconds, const std::string &pause_message = "");
};

typedef enum class ERR_TYPE {
  runtime_error, invalid_argument, out_of_range, domain_error, logic_error, length_error, bad_alloc, bad_cast, bad_typeid,
  overflow_error, underflow_error, range_error, ios_failure, err_code, custom_error
} err;

class Error: public std::exception {
  private:
    std::string error_message;

  public:
    Error() {};
    Error(const std::string &message): error_message(message) {}

    const char* what() const noexcept override {
      return error_message.c_str();
    }
};

class Exception {
  private:
    Exception() {}
    Exception(const Exception&) = delete;
    Exception& operator=(const Exception&) = delete;

  public:
    constexpr static Exception& instance() {
      static Exception instance;
      return instance;
    }

    Exception& raise(err err_type, const auto &message, const std::string &heading = "") noexcept {
      return *this;
    }
    Exception& raise_if(bool if_statement, err err_type, auto &message, const std::string &heading = "") noexcept {
      return *this;
    }

    Exception& log(auto &...Args) {
      ((std::cerr << Args), ...);
      return *this;
    }
};
