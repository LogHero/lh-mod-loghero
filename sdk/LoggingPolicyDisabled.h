#ifndef LOGGINGPOLICYDISABLED_H
#define LOGGINGPOLICYDISABLED_H

#include "GlobalDefines.h"

#include <string>


namespace loghero {

  class LoggingPolicyDisabled {
    public:
      DISALLOW_COPY_AND_ASSIGN(LoggingPolicyDisabled);

      static void debug(const std::string &){}
      static void info(const std::string &){}
      static void warning(const std::string &){}
      static void error(const std::string &){}
      static void fatal(const std::string &){}

    private:
      LoggingPolicyDisabled();
      ~LoggingPolicyDisabled();
  };

}


#endif // LOGGINGPOLICYDISABLED_H
