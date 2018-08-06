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
      LogHeroSession(const LogHeroSettings &settings);
      virtual ~LogHeroSession();

      // TODO: This method is not thread save
      virtual void submitLogEvent(const LogEvent &logEvent);

    private:
      LogHeroSettings settings;
  };

  template <class HttpRequestT, class SerializerT>
  LogHeroSession<HttpRequestT, SerializerT>::LogHeroSession(const LogHeroSettings &settings):
  settings(settings) {
  }

  template <class HttpRequestT, class SerializerT>
  LogHeroSession<HttpRequestT, SerializerT>::~LogHeroSession() {
  }

  template <class HttpRequestT, class SerializerT>
  void LogHeroSession<HttpRequestT, SerializerT>::submitLogEvent(const LogEvent &logEvent) {
    loghero::LogEvent::List logEventList;
    logEventList.push_back(logEvent);
    loghero::APIAccess<HttpRequestT, SerializerT> apiAccess(this->settings);
    apiAccess.submitLogEvents(logEventList);
  }

  typedef LogHeroSession<HttpRequestCurl, LogEventSerializerJson> LogHeroDefaultSession;

}

#endif // LOGHEROSESSION_H
