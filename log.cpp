#include "log.h"

namespace {
  std::string get_error_Type(err err_type) noexcept {
    switch(err_type) {
      case err::runtime_error: return "Runtime-Error";
      case err::invalid_argument: return "Invalid-Argument";
      case err::out_of_range: return "Out-Of-Range";
      case err::domain_error: return "Domain-Error";
      case err::logic_error: return "Logic-Error";
      case err::length_error: return "Length-Error";
      case err::bad_alloc: return "Bad-Alloc";
      case err::bad_cast: return "Bad-Cast";
      case err::bad_typeid: return "Bad-TypeID";
      case err::overflow_error: return "Overflow-Error";
      case err::underflow_error: return "Underflow-Error";
      case err::range_error: return "Range-Error";
      case err::ios_failure: return "IOS-Failure";
      case err::err_code: return "Error-Code";
      default: return std::string();
    }
  }
}

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
  if(seconds < 0) error.raise("Can't sleep for negative seconds.", err::invalid_argument);
  std::this_thread::sleep_for(std::chrono::milliseconds((size_t)(1000*seconds)));
  return *this;
}

Console& Console::pause_ms(size_t milliseconds, const std::string &pause_message) {
  std::cout << pause_message;
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
  return *this;
}

//---------------------------EXCEPTION----------------------------//

Exception& Exception::raise(const std::string &message, err err_type, const std::string &heading, bool throw_err) noexcept {
  Error error(get_error_Type(err_type) + "\n\t" + heading + "\n\t" + message);
  if(throw_err) throw error;
  else std::cerr << error.what();
  return *this;
}

Exception& Exception::raise_if(bool if_statement, const std::string &message, err err_type, const std::string &heading, bool throw_err) noexcept {
  if(!if_statement) return *this;
  Error error(get_error_Type(err_type) + "\n\t" + heading + "\n\t" + message);
  if(throw_err) throw error;
  else std::cerr << error.what();
  return *this;
}

Exception& Exception::raise_ifn(bool if_statement, const std::string &message, err err_type, const std::string &heading, bool throw_err) noexcept {
  if(if_statement) return *this;
  Error error(get_error_Type(err_type) + "\n\t" + heading + "\n\t" + message);
  if(throw_err) throw error;
  else std::cerr << error.what();
  return *this;
}
