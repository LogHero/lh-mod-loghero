#ifndef APIACCESS_H
#define APIACCESS_H

#include "LogHeroSettings.h"
#include "Zlib.h"


namespace loghero {

  template <class HttpRequestT>
  class APIAccess {
    public:
      APIAccess(const LogHeroSettings &settings);
      virtual ~APIAccess(){}

      void submitLogPackage(const std::string &payloadAsJson) const;

    private:
      const LogHeroSettings settings;
      const std::string userAgent;

  };

  template <class HttpRequestT>
  APIAccess<HttpRequestT>::APIAccess(const LogHeroSettings &settings):
    settings(settings),
    userAgent(settings.clientId + "; C++ SDK loghero/sdk@0.0.1") {
  }

  template <class HttpRequestT>
  void APIAccess<HttpRequestT>::submitLogPackage(const std::string &payloadAsJson) const {
    HttpRequestT request;
    request.setMethod("PUT");
    request.setUrl(this->settings.apiEndpoint);
    request.setHeader("Content-type: application/json");
    request.setHeader("Authorization: " + this->settings.apiKey);
    request.setHeader("User-Agent: " + this->userAgent);
    request.setHeader("Content-encoding: deflate");
    request.setData(Zlib::deflate(payloadAsJson));
    request.execute();
  }

}

#endif // APIACCESS_H
