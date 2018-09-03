#ifndef LOGGING_H
#define LOGGING_H

#include "LoggingPolicyDisabled.h"

#ifdef LH_ENABLE_LOGGING
#include "LoggingPolicyBoost.h"
#endif // LH_ENABLE_LOGGING


namespace loghero {

  template <class LoggingPolicy>
  class Logging: public LoggingPolicy {
    public:
      DISALLOW_COPY_AND_ASSIGN(Logging);
    private:
      Logging();
      ~Logging();
  };

#ifdef LH_ENABLE_LOGGING
  typedef Logging<LoggingPolicyBoost> Log;
#else // LH_ENABLE_LOGGING
  typedef Logging<LoggingPolicyDisabled> Log;
#endif // LH_ENABLE_LOGGING
}

#endif // LOGGING_H
