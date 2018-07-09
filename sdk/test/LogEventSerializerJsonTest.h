#ifndef LOGEVENTSERIALIZERJSONTEST_H
#define LOGEVENTSERIALIZERJSONTEST_H

#include "LibLogHero.h"
#include "LogEvent.h"
#include "LogEventSerializerJson.h"
#include "gtest/gtest.h"

#include <memory>


namespace loghero {
namespace testing {

  class LogEventSerializerJsonTest : public ::testing::Test {
    public:

      LogEventSerializerJsonTest();
      virtual ~LogEventSerializerJsonTest();

      LogEvent::List logEvents;
      LogEventSerializerJson serializer;

  };

}
}

#endif // LOGEVENTSERIALIZERJSONTEST_H
