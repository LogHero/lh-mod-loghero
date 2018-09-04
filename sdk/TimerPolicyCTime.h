#ifndef TIMERPOLICYCTIME_H
#define TIMERPOLICYCTIME_H

#include "LogHeroSettings.h"
#include "Logging.h"

#include <chrono>

namespace loghero {

  class TimerPolicyCTime {
    public:

      typedef std::chrono::time_point<std::chrono::steady_clock> TimePointT;

      DISALLOW_COPY_AND_ASSIGN(TimerPolicyCTime);
      TimerPolicyCTime(const LogHeroSettings &settings);
      virtual ~TimerPolicyCTime();

      void reset();

      bool timeout() const;

    protected:

      static TimePointT getCurrentTimestamp();

      uint64_t timeoutInSeconds;
      TimePointT referenceTimestamp;

  };

  inline TimerPolicyCTime::TimerPolicyCTime(const LogHeroSettings &settings) :
    timeoutInSeconds(settings.logBufferTimeoutSeconds),
    referenceTimestamp(TimerPolicyCTime::getCurrentTimestamp()) {
  }

  inline TimerPolicyCTime::~TimerPolicyCTime() {
  }

  inline void TimerPolicyCTime::reset() {
    this->referenceTimestamp = this->getCurrentTimestamp();
  }

  inline bool TimerPolicyCTime::timeout() const {
    TimePointT now = TimerPolicyCTime::getCurrentTimestamp();
    std::chrono::duration<double> duration = now - this->referenceTimestamp;
    uint64_t secondsElapsed = static_cast<uint64_t>(duration.count());
    bool isTimeout = secondsElapsed >= this->timeoutInSeconds;
#ifdef LH_ENABLE_LOGGING
    if (isTimeout) {
      Log::debug("Timeout... dump needed");
    }
    else {
      std::stringstream strs;
      uint64_t secondsLeft = this->timeoutInSeconds - secondsElapsed;
      strs << secondsLeft << " seconds left until next timeout" << std::endl;
      Log::debug(strs.str());
    }
#endif // LH_ENABLE_LOGGING
    return isTimeout;
  }

  inline TimerPolicyCTime::TimePointT TimerPolicyCTime::getCurrentTimestamp() {
    return std::chrono::steady_clock::now();
  }

}

#endif // TIMERPOLICYCTIME_H
