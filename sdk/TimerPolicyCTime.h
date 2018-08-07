#ifndef TIMERPOLICYCTIME_H
#define TIMERPOLICYCTIME_H

#include <ctime>

namespace loghero {

  class TimerPolicyCTime {
    public:

      // TODO Pass via settings:
      TimerPolicyCTime(uint64_t timeoutInSeconds=500);
      virtual ~TimerPolicyCTime();

      void reset();

      bool timeout() const;

    protected:

      static std::clock_t getCurrentTimestamp();

      uint64_t timeoutInSeconds;
      std::clock_t referenceTimestamp;

  };

  inline TimerPolicyCTime::TimerPolicyCTime(uint64_t timeoutInSeconds) :
    timeoutInSeconds(timeoutInSeconds),
    referenceTimestamp(TimerPolicyCTime::getCurrentTimestamp()) {
  }

  inline TimerPolicyCTime::~TimerPolicyCTime() {
  }

  inline void TimerPolicyCTime::reset() {
    this->referenceTimestamp = this->getCurrentTimestamp();
  }

  inline bool TimerPolicyCTime::timeout() const {
    std::clock_t now = TimerPolicyCTime::getCurrentTimestamp();
    double secondsElapsed = static_cast<double>(now - this->referenceTimestamp) / CLOCKS_PER_SEC;
    return static_cast<uint64_t>(secondsElapsed) >= this->timeoutInSeconds;
  }

  inline std::clock_t TimerPolicyCTime::getCurrentTimestamp() {
    return std::clock();
  }

}

#endif // TIMERPOLICYCTIME_H
