#ifndef LOGGING_H
#define LOGGING_H

#include "LoggingPolicyBoost.h"


namespace loghero {

  template <class LoggingPolicy>
  class Logging {
    public:
      DISALLOW_COPY_AND_ASSIGN(Logging);

      static void debug(const std::string &message);

      static void init();

    private:
      Logging();
      ~Logging();
  };

  template <class LoggingPolicy>
  void Logging<LoggingPolicy>::init() {
    LoggingPolicy::init();
  }

  template <class LoggingPolicy>
  void Logging<LoggingPolicy>::debug(const std::string &message) {
    LoggingPolicy::debug(message);
  }

}

#endif // LOGGING_H
