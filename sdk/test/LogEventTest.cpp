#include "LogEventTest.h"

namespace loghero {
namespace testing {

  LogEventTest::LogEventTest() {
    this->cLogEvent.hostname = "www.loghero.io";
    this->cLogEvent.landingPagePath = "/landing/page/path";
    this->cLogEvent.ipAddress = "123.45.67.89";
    this->cLogEvent.timestamp = 1530695457;
    this->cLogEvent.userAgent = "Google Bot";
  }

  LogEventTest::~LogEventTest() {

  }

  TEST_F(LogEventTest, InitializeFromLogHeroCStruct) {
    const LogEvent logEvent(this->cLogEvent);
    EXPECT_EQ("www.loghero.io", logEvent.getHostname());
    EXPECT_EQ("/landing/page/path", logEvent.getLandingPagePath());
    EXPECT_EQ("123.45.67.89", logEvent.getIpAddress());
    EXPECT_EQ("Google Bot", logEvent.getUserAgent());
    EXPECT_EQ(1530695457, logEvent.getTimestamp());
  }

  TEST_F(LogEventTest, InitializeTimestampAsString) {
    const LogEvent logEvent(this->cLogEvent);
    EXPECT_EQ("2018-07-04T11:10:57+0200", logEvent.getTimestampAsString());
  }

}
}
