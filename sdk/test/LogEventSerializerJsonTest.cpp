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
                                          "\"202cb962ac59075b964b07152d234b70.6c8349cc7260ae62e3b1396831a8398f.735b90b4568125ed6c3f678819b6e058.7647966b7343c29048673252e490f736\","
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
                                   "\"ipGroups\","
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
