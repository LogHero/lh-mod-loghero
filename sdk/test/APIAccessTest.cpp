#include "APIAccessTest.h"
#include "APIAccess.h"
#include "MockHttpRequest.h"
#include "FakeHttpRequest.h"


namespace loghero {
namespace testing {

  APIAccessTest::APIAccessTest() {
  }

  APIAccessTest::~APIAccessTest() {
  }

  TEST_F(APIAccessTest, DeflateLogPackageAndSendToAPI) {
    MockHttpRequest httpRequestMock;
    EXPECT_CALL(httpRequestMock, setMethod("PUT"));
    FakeHttpRequest::resetRequestMock(&httpRequestMock);
    APIAccess<FakeHttpRequest> apiAccess;
    apiAccess.submitLogPackage("LOG PACKAGE");
  }

}
}
