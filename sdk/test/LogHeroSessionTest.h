#ifndef LOGHEROSESSIONTEST_H
#define LOGHEROSESSIONTEST_H

#include "LogEvent.h"
#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogHeroSessionTest : public ::testing::Test {
    public:
      LogHeroSessionTest();

      static std::string buildExpectedPayload(const LogEvent::List &logEvents);
  };

}
}

#endif // LOGHEROSESSIONTEST_H
