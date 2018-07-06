#ifndef MOCKHTTPREQUEST_H
#define MOCKHTTPREQUEST_H

#include "HttpRequestInterface.h"

#include "gmock/gmock.h"


namespace loghero {
namespace testing {

  class MockHttpRequest : public HttpRequestInterface {
    public:
      MOCK_METHOD1(setUrl, void(const std::string&));
      MOCK_METHOD1(setMethod, void(const std::string&));
      MOCK_METHOD1(setData, void(const std::string&));
      MOCK_METHOD1(setHeader, void(const std::string&));
      MOCK_METHOD0(execute, void());
  };

}
}

#endif // MOCKHTTPREQUEST_H
