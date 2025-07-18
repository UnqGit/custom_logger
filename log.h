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
    
    void log(const auto &arg) {std::cout << arg;} // Log to the console.
    void logln(const auto &arg) {std::cout << arg << '\n';} // Log to the console with a newline character at the end.
    void log(const auto &...Args) {((std::cout << Args), ...);} // Logs multiple inputs without a space in between.
    void logln(const auto &...Args) {
      ((std::cout << Args), ...);
      std::cout << '\n';
    }
    void logs(const auto &...Args) {((std::cout << Args << ' '), ...);}
    void log_sln(const auto &...Args) {
      ((std::cout << Args << ' '), ...);
      std::cout << '\n';
    }
    void log_mln(const auto &...Args) {((std::cout << Args << '\n'), ...);}
    template <typename... Args>
    void logf(const std::format_string<Args...> &fmt, Args&&... args) {
      std::print(fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void log_fln(const std::format_string<Args...> &fmt, Args&&... args) {
      std::println(fmt, std::forward<Args>(args)...);
    }
    
    bool get(auto &variable) { // Gives true, if occured successfully.
      bool successful = (std::cin >> variable);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return successful;
    }
    
    bool getln(auto &variable) {return std::getline(std::cin, variable);}
    
    bool getm(auto &...Args) {
      bool successful = true;
      successful &= (bool)((std::cin >> Args), ...);
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return successful;
    }
    
    void clog(const auto &...Args) {((std::cerr << Args), ...);}
    
    void pause(const std::string &pause_message = "");
    void pause(size_t seconds, const std::string &pause_message = "");
    void pause(float seconds, const std::string &pause_message = "");
    void pause_ms(size_t milliseconds, const std::string &pause_message = "");
};

enum class ERR {
  runtime_error, invalid_argument, out_of_range, domain_error, logic_error, length_error, bad_alloc, bad_cast, bad_typeid,
  overflow_error, underflow_error, range_error, ios_failure, custom_error
};

class Exception {
  private:
    Exception() = delete;
};
