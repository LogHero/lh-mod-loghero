#include "TimerPolicyTest.h"
#include "TimerPolicyCTime.h"

namespace loghero {
namespace testing {

  class TimerPolicyForTesting: public TimerPolicyCTime {
    public:
      TimerPolicyForTesting(uint64_t timeoutSeconds = 500):
        TimerPolicyCTime(timeoutSeconds) {
      }

      std::clock_t getReferenceTimestamp() {
        return this->referenceTimestamp;
      }

      void setReferenceTimestamp(std::clock_t timestamp) {
        this->referenceTimestamp = timestamp;
      }
  };

  TimerPolicyTest::TimerPolicyTest() {

  }

  TEST_F(TimerPolicyTest, ResetTimer) {
    std::clock_t ts1 = std::clock();
    TimerPolicyForTesting policy;
    ASSERT_LE(ts1, policy.getReferenceTimestamp());
    std::clock_t ts2 = std::clock();
    ASSERT_GE(ts2, policy.getReferenceTimestamp());
    policy.reset();
    ASSERT_LE(ts2, policy.getReferenceTimestamp());
  }

  TEST_F(TimerPolicyTest, Timeout) {
    std::clock_t now = std::clock();
    TimerPolicyForTesting policy(60);
    ASSERT_FALSE(policy.timeout());
    policy.setReferenceTimestamp(now + 100 * CLOCKS_PER_SEC);
    ASSERT_TRUE(policy.timeout());
  }

}}
