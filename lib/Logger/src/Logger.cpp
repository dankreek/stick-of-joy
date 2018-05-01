#include <Arduino.h>
#include "Logger.hpp"

namespace dankreek {
  void Logger::init() {
    Serial.begin(9600);
  }

  Logger::Logger() {
    this->_className = "";
  }

  Logger::Logger(const char* className) {
    this->_className = className;
  }
}
