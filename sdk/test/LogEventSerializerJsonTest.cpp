#include "LogEventSerializerJsonTest.h"
#include "LibTestSamples.h"
#include "LogEventSerializerJson.h"


namespace loghero {
namespace testing {

  LogEventSerializerJsonTest::LogEventSerializerJsonTest() :
  pSerializer(new LogEventSerializerJson()) {
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
    this->logEvents.push_back(LogEvent(createCLogEventSample()));
  }

  LogEventSerializerJsonTest::~LogEventSerializerJsonTest() {
  }

  TEST_F(LogEventSerializerJsonTest, SerializeLogEventList) {
    std::string jsonExpected = "{\"columns\":[\"hostname\",\"landingPage\",\"timesamp\",\"ua\"]}";
    std::string jsonCreated = pSerializer->serialize(this->logEvents);
    ASSERT_EQ(jsonExpected, jsonCreated);
  }

  // TODO
  TEST_F(LogEventSerializerJsonTest, SerializeEmptyLogEventList) {
  }

}
}
