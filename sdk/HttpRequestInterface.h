#ifndef HTTPREQUESTINTERFACE_H
#define HTTPREQUESTINTERFACE_H

#include "GlobalDefines.h"


namespace loghero {

  class HttpRequestInterface {
    public:

      DISALLOW_COPY_AND_ASSIGN(HttpRequestInterface);
      HttpRequestInterface(){}
      virtual ~HttpRequestInterface(){}

  };

}

#endif // HTTPREQUESTINTERFACE_H
