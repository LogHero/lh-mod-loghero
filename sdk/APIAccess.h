#ifndef APIACCESS_H
#define APIACCESS_H

#include "APIAccessInterface.h"
#include "Zlib.h"


namespace loghero {

  template <class HttpRequestT>
  class APIAccess : public APIAccessInterface {
    public:
      APIAccess(){}
      virtual ~APIAccess(){}

      virtual void submitLogPackage(const std::string &payloadAsJson) const;

  };

  template <class HttpRequestT>
  void APIAccess<HttpRequestT>::submitLogPackage(const std::string &payloadAsJson) const {
    HttpRequestT request;
    request.setMethod("PUT");
    request.setUrl("https://test.loghero.io/logs/");
    request.setHeader("Content-type: application/json");
    request.setHeader("Authorization: YOUR_API_KEY");
    request.setHeader("User-Agent: C++ SDK Prototype");
    request.setHeader("Content-encoding: deflate");
    request.setData(Zlib::deflate(payloadAsJson));
    request.execute();
  }

}

#endif // APIACCESS_H
