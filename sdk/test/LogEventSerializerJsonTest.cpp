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
                                          "\"www.loghero.io\","
                                          "\"/landing/page/path\","
                                          "\"PUT\","
                                          "201,"
                                          "\"" + createSampleTimestampAsString() + "\","
                                          "\"Google Bot\""
                                        "]";
    const std::string jsonExpected = "{"
                                 "\"columns\":["
                                   "\"cid\","
                                   "\"hostname\","
                                   "\"landingPage\","
                                   "\"method\","
                                   "\"statusCode\","
                                   "\"timesamp\","
                                   "\"ua\""
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
