#ifndef APIACCESS_H
#define APIACCESS_H

#include "LogHeroSettings.h"
#include "LogEvent.h"
#include "Zlib.h"


namespace loghero {

  template <class HttpRequestT, class SerializerT>
  class APIAccess {
    public:
      APIAccess(const LogHeroSettings &settings);
      virtual ~APIAccess(){}

      void submitLogPackage(const LogEvent::List &logEvents) const;

    private:
      const LogHeroSettings settings;
      const std::string userAgent;
      const SerializerT serializer;

  };

  template <class HttpRequestT, class SerializerT>
  APIAccess<HttpRequestT, SerializerT>::APIAccess(const LogHeroSettings &settings):
    settings(settings),
    userAgent(settings.clientId + "; C++ SDK loghero/sdk@0.0.1") {
  }

  template <class HttpRequestT, class SerializerT>
  void APIAccess<HttpRequestT, SerializerT>::submitLogPackage(const LogEvent::List &logEvents) const {
    HttpRequestT request;
    request.setMethod("PUT");
    request.setUrl(this->settings.apiEndpoint);
    request.setHeader("Content-type: application/json");
    request.setHeader("Authorization: " + this->settings.apiKey);
    request.setHeader("User-Agent: " + this->userAgent);
    request.setHeader("Content-encoding: deflate");
    const std::string payloadAsJson = this->serializer.serialize(logEvents);
    request.setData(Zlib::deflate(payloadAsJson));
    request.execute();
  }

}

#endif // APIACCESS_H
