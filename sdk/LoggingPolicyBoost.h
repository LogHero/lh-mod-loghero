#ifndef LOGGINGPOLICYBOOST_H
#define LOGGINGPOLICYBOOST_H

#include "GlobalDefines.h"

#include <string>


namespace loghero {

  class LoggingPolicyBoost {
    public:
      DISALLOW_COPY_AND_ASSIGN(LoggingPolicyBoost);

      static void debug(const std::string &message);
      static void info(const std::string &message);
      static void warning(const std::string &message);
      static void error(const std::string &message);
      static void fatal(const std::string &message);

      static void init(const std::string &logDirectory, const std::string &logLevel);

    private:
      LoggingPolicyBoost();
      ~LoggingPolicyBoost();

      static bool loggingIsSetup;
  };

}

#endif // LOGGINGPOLICYBOOST_H
