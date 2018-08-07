#include "LogEventTest.h"
#include "LibTestSamples.h"

namespace loghero {
namespace testing {

  LogEventTest::LogEventTest() :
  cLogEvent(createCLogEventSample()) {
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
    EXPECT_EQ(createSampleTimestampAsString(), logEvent.getTimestampAsString());
  }

  TEST_F(LogEventTest, GenerateCidFromMd5HashOfIpAndUserAgent) {
    const LogEvent logEvent(this->cLogEvent);
    EXPECT_EQ("e254fc99d969b359dbb498b8ab8e5ee5", logEvent.getCid());
  }

  TEST_F(LogEventTest, GeneratMd5HashOfIp) {
    const LogEvent logEvent(this->cLogEvent);
    EXPECT_EQ("03de6422045e4ed3ac822c673ace32d1", logEvent.getIpHash());
  }

  TEST_F(LogEventTest, HandleNullCString) {
    this->cLogEvent.referer = NULL;
    this->cLogEvent.userAgent = NULL;
    this->cLogEvent.landingPagePath = NULL;
    this->cLogEvent.ipAddress = NULL;
    this->cLogEvent.hostname = NULL;
    this->cLogEvent.method = NULL;
    const LogEvent logEvent(this->cLogEvent);
    EXPECT_EQ("", logEvent.getReferer());
    EXPECT_EQ("", logEvent.getUserAgent());
    EXPECT_EQ("", logEvent.getLandingPagePath());
    EXPECT_EQ("", logEvent.getIpAddress());
    EXPECT_EQ("", logEvent.getHostname());
    EXPECT_EQ("", logEvent.getMethod());
    EXPECT_EQ("d41d8cd98f00b204e9800998ecf8427e", logEvent.getIpHash());
    EXPECT_EQ("d41d8cd98f00b204e9800998ecf8427e", logEvent.getCid());
  }

}
}
