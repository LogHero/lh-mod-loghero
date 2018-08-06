#ifndef LOGHEROSESSIONTEST_H
#define LOGHEROSESSIONTEST_H

#include "LogEvent.h"
#include "LogHeroSettings.h"
#include "LogContainerPolicyInMemory.h"
#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogHeroSessionTest : public ::testing::Test {
    public:
      LogHeroSessionTest();

      static std::string buildExpectedPayload(const LogEvent::List &logEvents);

      LogHeroSettings settings;
      LogContainerPolicyInMemory::Settings bufferSettings;
  };

}
}

#endif // LOGHEROSESSIONTEST_H
