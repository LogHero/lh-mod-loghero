#ifndef TIMERPOLICYMOCK_H
#define TIMERPOLICYMOCK_H

#include "LogHeroSettings.h"
#include "gmock/gmock.h"

namespace loghero {
namespace testing {

  class TimerPolicyMock {
    public:

      TimerPolicyMock(const LogHeroSettings settings = LogHeroSettings("SOME_API_KEY")):
        elapsedTimeSeconds(0) {
      }

      void reset() {
        this->pMockInstance->mockedReset();
      }

      bool timeout() const {
        return this->pMockInstance->elapsedTimeSeconds > 30;
      }

      static void resetMockInstance(TimerPolicyMock *pMockInstance) {
        TimerPolicyMock::pMockInstance = pMockInstance;
      }

      void setTimeElapsedSeconds(uint64_t elapsedTimeSeconds) {
        this->elapsedTimeSeconds = elapsedTimeSeconds;
      }

      MOCK_METHOD0(mockedReset, void());
      MOCK_METHOD0(mockedTimeElapsed, void());

    private:
      static TimerPolicyMock *pMockInstance;
      uint64_t elapsedTimeSeconds;
  };

}}

#endif // TIMERPOLICYMOCK_H
