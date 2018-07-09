#ifndef LOGEVENTTEST_H
#define LOGEVENTTEST_H

#include "LibLogHero.h"
#include "LogEvent.h"
#include "gtest/gtest.h"

namespace loghero {
namespace testing {

  class LogEventTest : public ::testing::Test {
    public:

      LogEventTest();
      virtual ~LogEventTest();

      ::LogEvent cLogEvent;

  };

}
}


#endif // LOGEVENTTEST_H
