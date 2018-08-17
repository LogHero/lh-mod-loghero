#include "SubmitPolicyAsyncTest.h"
#include "SubmitPolicyAsync.h"
#include "LogHeroSession.h"
#include "FakeHttpRequest.h"
#include "MockHttpRequest.h"
#include "LibTestSamples.h"
#include "LogHeroSessionTest.h"


namespace loghero {
namespace testing {

  class SubmitPolicyAsyncForTestung : public SubmitPolicyAsync<DefaultLogBuffer, FakeHttpRequest, LogEventSerializerJson> {
    public:
      SubmitPolicyAsyncForTestung(const LogHeroSettings &settings) :
        SubmitPolicyAsync<DefaultLogBuffer, FakeHttpRequest, LogEventSerializerJson>(settings) {
        this->launchPolicy = std::launch::deferred;
      }

      auto dumpAndSubmitAsync(BufferT *pLogBuffer) {
        return this->dumpAndSubmit(pLogBuffer);
      }
  };

  SubmitPolicyAsyncTest::SubmitPolicyAsyncTest():
    settings("SOME_API_KEY") {
  }

  TEST_F(SubmitPolicyAsyncTest, DumpAndSubmitAsync) {
    LogEvent logEvent(createCLogEventSample());
    DefaultLogBuffer logBuffer(this->settings);
    logBuffer.push(logEvent);
    LogEvent::List logEventListPushExpected;
    logEventListPushExpected.push_back(logEvent);
    const std::string expectedPayload = LogHeroSessionTest::buildExpectedPayload(logEventListPushExpected);
    SubmitPolicyAsyncForTestung submitPolicy(this->settings);
    auto handle = submitPolicy.dumpAndSubmitAsync(&logBuffer);
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
    handle.get();
  }

}}
