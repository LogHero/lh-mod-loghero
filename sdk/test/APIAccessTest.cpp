#include "APIAccessTest.h"
#include "APIAccess.h"
#include "MockHttpRequest.h"
#include "FakeHttpRequest.h"
#include "Zlib.h"


namespace loghero {
namespace testing {

  APIAccessTest::APIAccessTest():
    logHeroSettings("SOME_API_KEY", "Test Client"){
    logHeroSettings.apiEndpoint = "https://test.loghero.io/logs/";
  }

  APIAccessTest::~APIAccessTest() {
  }

  TEST_F(APIAccessTest, DeflateLogPackageAndSendToAPI) {
    MockHttpRequest httpRequestMock;
    EXPECT_CALL(httpRequestMock, setMethod("PUT"));
    EXPECT_CALL(httpRequestMock, setUrl("https://test.loghero.io/logs/"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-type: application/json"));
    EXPECT_CALL(httpRequestMock, setHeader("Authorization: SOME_API_KEY"));
    EXPECT_CALL(httpRequestMock, setHeader("User-Agent: Test Client; C++ SDK loghero/sdk@0.0.1"));
    EXPECT_CALL(httpRequestMock, setHeader("Content-encoding: deflate"));
    EXPECT_CALL(httpRequestMock, setData(Zlib::deflate("LOG PACKAGE")));
    EXPECT_CALL(httpRequestMock, execute());
    FakeHttpRequest::resetRequestMock(&httpRequestMock);
    APIAccess<FakeHttpRequest> apiAccess(this->logHeroSettings);
    apiAccess.submitLogPackage("LOG PACKAGE");
  }

}
}
