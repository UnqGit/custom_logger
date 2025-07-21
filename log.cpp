#include "log.h"

Console &console = Console::instance();
Exception &error = Exception::instance();

//------------------------------CONSOLE----------------------------//

Console& Console::pause(const std::string &pause_message) {
  std::cout << pause_message;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return *this;
}

Console& Console::pause(size_t seconds, const std::string &pause_message) {
  std::cout << pause_message;
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
  return *this;
}

Console& Console::pause(float seconds, const std::string &pause_message) {
  std::cout << pause_message;
  if(seconds < 0) throw std::invalid_argument("Can't sleep for negative seconds.");
  std::this_thread::sleep_for(std::chrono::milliseconds((size_t)(1000*seconds)));
  return *this;
}

Console& Console::pause_ms(size_t milliseconds, const std::string &pause_message) {
  std::cout << pause_message;
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  return *this;
}

//---------------------------EXCEPTION----------------------------//

