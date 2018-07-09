#include "LogHeroSessionTest.h"
#include "LibTestSamples.h"
#include "LogHeroSession.h"
#include "LogEventSerializerJson.h"
#include "Zlib.h"
#include "MockHttpRequest.h"
#include "FakeHttpRequest.h"


namespace loghero {
namespace testing {

  LogHeroSessionTest::LogHeroSessionTest() {

  }

  TEST_F(LogHeroSessionTest, DeflateLogEventAndSendToAPI) {
    LogEvent logEvent(createCLogEventSample());
    LogEvent::List logEventList;
    logEventList.push_back(logEvent);
    const std::string expectedPayload = this->buildExpectedPayload(logEventList);
    MockHttpRequest httpRequestMock;
    EXPECT_CALL(httpRequestMock, setMethod("PUT"));
    EXPECT_CALL(httpRequestMock, setUrl("https://test.loghero.io/logs/"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-type: application/json"));
    // TODO!!
    //EXPECT_CALL(httpRequestMock, setHeader("Authorization: SOME_API_KEY"));
    EXPECT_CALL(httpRequestMock, setHeader("Authorization: YOUR_API_KEY"));
    // TODO!!
    //EXPECT_CALL(httpRequestMock, setHeader("User-Agent: Test Client; C++ SDK loghero/sdk@0.0.1"));
    EXPECT_CALL(httpRequestMock, setHeader("User-Agent: Apache Module loghero/httpd@0.0.1; C++ SDK loghero/sdk@0.0.1"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-encoding: deflate"));
    EXPECT_CALL(httpRequestMock, setData(expectedPayload));
    EXPECT_CALL(httpRequestMock, execute());
    FakeHttpRequest::resetRequestMock(&httpRequestMock);
    LogHeroSession<FakeHttpRequest, LogEventSerializerJson> session;
    session.submitLogEvent(logEvent);
  }

  std::string LogHeroSessionTest::buildExpectedPayload(const LogEvent::List &logEvents) {
    LogEventSerializerJson serializer;
    return Zlib::deflate(serializer.serialize(logEvents));
  }

}
}
