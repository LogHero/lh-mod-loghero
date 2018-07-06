#ifndef HTTPREQUESTCURL_H
#define HTTPREQUESTCURL_H

#include "HttpRequestInterface.h"

#include <memory>


namespace loghero {

  class HttpRequestCurl : public HttpRequestInterface {
    public:
      HttpRequestCurl();
      virtual ~HttpRequestCurl();

      virtual void setUrl(const std::string &url);

      virtual void setMethod(const std::string &method);

      virtual void setData(const std::string &data);

      virtual void setHeader(const std::string &header);

      virtual void execute();

    private:

      struct CurlContainer;

      std::unique_ptr<CurlContainer> pCurlContainer;
  };

}


#endif // HTTPREQUESTCURL_H
