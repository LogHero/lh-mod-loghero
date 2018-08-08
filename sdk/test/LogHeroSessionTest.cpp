#include "LogHeroSessionTest.h"
#include "LibTestSamples.h"
#include "LogHeroSession.h"
#include "LogEventSerializerJson.h"
#include "Zlib.h"
#include "MockHttpRequest.h"
#include "FakeHttpRequest.h"


namespace loghero {
namespace testing {

  LogHeroSessionTest::LogHeroSessionTest():
    settings("SOME_API_KEY") {
    settings.maxLogEventsInBuffer = 3;
  }

  TEST_F(LogHeroSessionTest, DeflateLogEventAndSendToAPI) {
    LogEvent logEvent(createCLogEventSample());
    LogEvent::List logEventListPushExpected;
    logEventListPushExpected.push_back(logEvent);
    logEventListPushExpected.push_back(logEvent);
    logEventListPushExpected.push_back(logEvent);
    const std::string expectedPayload = this->buildExpectedPayload(logEventListPushExpected);
    MockHttpRequest httpRequestMock;
    EXPECT_CALL(httpRequestMock, setMethod("PUT"));
    EXPECT_CALL(httpRequestMock, setUrl("https://test.loghero.io/logs/"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-type: application/json"));
    EXPECT_CALL(httpRequestMock, setHeader("Authorization: SOME_API_KEY"));
    EXPECT_CALL(httpRequestMock, setHeader("User-Agent: Apache Module loghero/httpd@0.0.1; C++ SDK loghero/sdk@0.0.1"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-encoding: deflate"));
    EXPECT_CALL(httpRequestMock, setData(expectedPayload));
    EXPECT_CALL(httpRequestMock, execute());
    FakeHttpRequest::resetRequestMock(&httpRequestMock);
    LogHeroSession<DefaultLogBuffer, FakeHttpRequest, LogEventSerializerJson> session(settings);
    session.submitLogEvent(logEvent);
    session.submitLogEvent(logEvent);
    session.submitLogEvent(logEvent);
    session.submitLogEvent(logEvent);
    session.submitLogEvent(logEvent);
  }

  std::string LogHeroSessionTest::buildExpectedPayload(const LogEvent::List &logEvents) {
    LogEventSerializerJson serializer;
    return Zlib::deflate(serializer.serialize(logEvents));
  }

}
}
