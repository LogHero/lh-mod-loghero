#ifndef HTTPREQUESTINTERFACE_H
#define HTTPREQUESTINTERFACE_H

#include "GlobalDefines.h"

#include <string>


namespace loghero {

  class HttpRequestInterface {
    public:

      DISALLOW_COPY_AND_ASSIGN(HttpRequestInterface);
      HttpRequestInterface(){}
      virtual ~HttpRequestInterface(){}

      virtual void setUrl(const std::string &url) = 0;

      virtual void setMethod(const std::string &method) = 0;

      virtual void setData(const std::string &data) = 0;

      virtual void setHeader(const std::string &header) = 0;

      virtual void execute() = 0;

  };

}

#endif // HTTPREQUESTINTERFACE_H
