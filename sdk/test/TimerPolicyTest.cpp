#include "TimerPolicyTest.h"
#include "TimerPolicyCTime.h"

namespace loghero {
namespace testing {

  class TimerPolicyForTesting: public TimerPolicyCTime {
    public:
      TimerPolicyForTesting(const LogHeroSettings &settings):
        TimerPolicyCTime(settings) {
      }

      TimePointT getReferenceTimestamp() {
        return this->referenceTimestamp;
      }

      void setReferenceTimestamp(TimePointT timestamp) {
        this->referenceTimestamp = timestamp;
      }
  };

  TimerPolicyTest::TimerPolicyTest():
    settings("YOUR_API_KEY") {
  }

  TEST_F(TimerPolicyTest, ResetTimer) {
    TimerPolicyCTime::TimePointT ts1 = std::chrono::steady_clock::now();
    TimerPolicyForTesting policy(this->settings);
    ASSERT_LE(ts1, policy.getReferenceTimestamp());
    TimerPolicyCTime::TimePointT ts2 = std::chrono::steady_clock::now();
    ASSERT_GE(ts2, policy.getReferenceTimestamp());
    policy.reset();
    ASSERT_LE(ts2, policy.getReferenceTimestamp());
  }

  TEST_F(TimerPolicyTest, Timeout) {
    this->settings.logBufferTimeoutSeconds = 60;
    TimerPolicyCTime::TimePointT now = std::chrono::steady_clock::now();
    TimerPolicyForTesting policy(this->settings);
    ASSERT_FALSE(policy.timeout());
    policy.setReferenceTimestamp(now + std::chrono::seconds(100));
    ASSERT_TRUE(policy.timeout());
  }

}}
