#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

namespace dankreek {

  class Logger {
  public:
    static void init();

    Logger();
    Logger(const char* className);

    template <typename H, typename... T> void log(H p, T... t) {
      Serial.print('[');
      Serial.print(this->_className);
      Serial.print(']');
      Serial.print(' ');
      Serial.print(p);
      this->_log(t...);
    }

  protected:
    void _log() {
      Serial.println();
    }
    template <typename H, typename... T> void _log(H p, T... t) {
      Serial.print(p);
      this->_log(t...);
    }

    const char* _className;
  };
}

#endif
