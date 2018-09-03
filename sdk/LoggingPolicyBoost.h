#ifndef LOGGINGPOLICYBOOST_H
#define LOGGINGPOLICYBOOST_H

#include "GlobalDefines.h"

#include <string>


namespace loghero {

  class LoggingPolicyBoost {
    public:
      DISALLOW_COPY_AND_ASSIGN(LoggingPolicyBoost);

      static void debug(const std::string &message);

      static void init();

    private:
      LoggingPolicyBoost();
      ~LoggingPolicyBoost();
  };

}

#endif // LOGGINGPOLICYBOOST_H
