#ifndef FAKEHTTPREQUEST_H
#define FAKEHTTPREQUEST_H

#include "HttpRequestInterface.h"

#include <cassert>


namespace loghero {
namespace testing {

  class FakeHttpRequest : public HttpRequestInterface {
    public:

      static void resetRequestMock(HttpRequestInterface *pRequestMock) {
        FakeHttpRequest::pRequestMock = pRequestMock;
      }

      virtual void setUrl(const std::string &url) {
        assert(FakeHttpRequest::pRequestMock);
        FakeHttpRequest::pRequestMock->setUrl(url);
      }

      virtual void setMethod(const std::string &method){
        assert(FakeHttpRequest::pRequestMock);
        FakeHttpRequest::pRequestMock->setMethod(method);
      }

      virtual void setData(const std::string &data) {
        assert(FakeHttpRequest::pRequestMock);
        FakeHttpRequest::pRequestMock->setData(data);
      }

      virtual void setHeader(const std::string &header) {
        assert(FakeHttpRequest::pRequestMock);
        FakeHttpRequest::pRequestMock->setHeader(header);
      }

      virtual void execute() {
        assert(FakeHttpRequest::pRequestMock);
        FakeHttpRequest::pRequestMock->execute();
        FakeHttpRequest::pRequestMock = NULL;
      }

    private:

      static HttpRequestInterface *pRequestMock;

  };

}
}

#endif // FAKEHTTPREQUEST_H
