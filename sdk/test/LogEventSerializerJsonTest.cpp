#include "LogEventSerializerJsonTest.h"
#include "LibTestSamples.h"
#include "LogEventSerializerJson.h"


namespace loghero {
namespace testing {

  LogEventSerializerJsonTest::LogEventSerializerJsonTest() {
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
  }

  LogEventSerializerJsonTest::~LogEventSerializerJsonTest() {
  }

  TEST_F(LogEventSerializerJsonTest, SerializeLogEventList) {
    const std::string rowJsonExpected = "["
                                          "\"e254fc99d969b359dbb498b8ab8e5ee5\","
                                          "\"03de6422045e4ed3ac822c673ace32d1\","
                                          "\"www.loghero.io\","
                                          "\"/landing/page/path\","
                                          "\"PUT\","
                                          "201,"
                                          "\"" + createSampleTimestampAsString() + "\","
                                          "123,"
                                          "\"Google Bot\","
                                          "\"www.google.de\""
                                        "]";
    const std::string jsonExpected = "{"
                                 "\"columns\":["
                                   "\"cid\","
                                   "\"ip\","
                                   "\"hostname\","
                                   "\"landingPage\","
                                   "\"method\","
                                   "\"statusCode\","
                                   "\"timesamp\","
                                   "\"pageLoadTime\","
                                   "\"ua\","
                                   "\"referer\""
                                 "],"
                                 "\"rows\":["
                                   + rowJsonExpected + ","
                                   + rowJsonExpected + ","
                                   + rowJsonExpected +
                                 "]"
                               "}";
    std::string jsonCreated = serializer.serialize(this->logEvents);
    ASSERT_EQ(jsonExpected, jsonCreated);
  }

}
}
