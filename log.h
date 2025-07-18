#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <print>
#include <format>
#include <string>
#include <concepts>

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
    
    void log(const auto &arg) {
      std::cout << arg;
    }
    void logln(const auto &arg) {
      std::cout << arg << '\n';
    }
    void log(const auto &...Args) {
      ((std::cout << Args << ' '), ...);
    }
    void logln(const auto &...Args) {
      ((std::cout << Args << ' '), ...);
      std::cout << '\n';
    }
    void log_mln(const auto &...Args) {
      ((std::cout << Args << '\n'), ...);
    }
    template <typename... Args>
    void logf(const std::format_string<Args...> &fmt, Args&&... args) {
      std::print(fmt, std::forward<Args>(args)...);
    }
    template <typename... Args>
    void log_fln(const std::format_string<Args...> &fmt, Args&&... args) {
      std::println(fmt, std::forward<Args>(args)...);
    }
    
    // Gives true, if occured successfully.
    bool get(auto &variable) {
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
    
    void pause(const std::string &pause_message = "") {
      std::cout << pause_message;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    void pause(size_t seconds, const std::string &pause_message = "") {
      std::cout << pause_message;
      std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }
    void pause_ms(size_t milliseconds, const std::string &pause_message = "") {
      std::cout << pause_message;
      std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    void pause_ms(float seconds, const std::string &pause_message = "") {
      std::cout << pause_message;
      if(seconds < 0) throw std::invalid_argument("Can't sleep for negative seconds.");
      std::this_thread::sleep_for(std::chrono::milliseconds((size_t)(1000*seconds)));
    }
};
