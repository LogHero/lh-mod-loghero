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

      void submitLogEvents(const LogEvent::List &logEvents) const;

    private:
      const LogHeroSettings settings;
      const std::string userAgent;
      const SerializerT serializer;

  };

  template <class HttpRequestT, class SerializerT>
  APIAccess<HttpRequestT, SerializerT>::APIAccess(const LogHeroSettings &settings):
    settings(settings),
    userAgent(std::string(LH_MOD_CLIENT_ID) + "; " + std::string(LH_SDK_CLIENT_ID)) {
  }

  template <class HttpRequestT, class SerializerT>
  void APIAccess<HttpRequestT, SerializerT>::submitLogEvents(const LogEvent::List &logEvents) const {
    HttpRequestT request;
    request.setMethod("PUT");
    request.setUrl(this->settings.apiEndpoint);
    request.setHeader("Content-type: application/json");
    request.setHeader("Authorization: " + this->settings.apiKey);
    request.setHeader("User-Agent: " + this->userAgent);
    request.setHeader("Content-encoding: deflate");
    const std::string payloadDeflated = Zlib::deflate(this->serializer.serialize(logEvents));
    request.setData(payloadDeflated);
    request.execute();
  }

}

#endif // APIACCESS_H
