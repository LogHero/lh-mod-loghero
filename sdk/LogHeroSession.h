#ifndef LOGHEROSESSION_H
#define LOGHEROSESSION_H

#include "LogHeroSessionInterface.h"
#include "LogHeroSettings.h"
#include "APIAccess.h"
#include "HttpRequestCurl.h"
#include "LogEventSerializerJson.h"


namespace loghero {

  template <class HttpRequestT, class SerializerT>
  class LogHeroSession : public LogHeroSessionInterface {
    public:
      DISALLOW_COPY_AND_ASSIGN(LogHeroSession);
      LogHeroSession();
      virtual ~LogHeroSession();

      virtual void submitLogEvent(const LogEvent &logEvent);
  };

  template <class HttpRequestT, class SerializerT>
  LogHeroSession<HttpRequestT, SerializerT>::LogHeroSession() {
  }

  template <class HttpRequestT, class SerializerT>
  LogHeroSession<HttpRequestT, SerializerT>::~LogHeroSession() {
  }

  template <class HttpRequestT, class SerializerT>
  void LogHeroSession<HttpRequestT, SerializerT>::submitLogEvent(const LogEvent &logEvent) {
    loghero::LogEvent::List logEventList;
    logEventList.push_back(logEvent);
    loghero::LogHeroSettings settings("YOUR_API_KEY", "Apache Module loghero/httpd@0.0.1");
    loghero::APIAccess<HttpRequestT, SerializerT> apiAccess(settings);
    apiAccess.submitLogEvents(logEventList);
  }

  typedef LogHeroSession<HttpRequestCurl, LogEventSerializerJson> LogHeroDefaultSession;

}

#endif // LOGHEROSESSION_H
