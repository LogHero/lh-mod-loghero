#ifndef LOGHEROSESSION_H
#define LOGHEROSESSION_H

#include "LogHeroSessionInterface.h"
#include "LogHeroSettings.h"
#include "APIAccess.h"
#include "LogBuffer.h"
#include "LogContainerPolicyInMemory.h"
#include "TimerPolicyCTime.h"
#include "HttpRequestCurl.h"
#include "LogEventSerializerJson.h"


namespace loghero {

  template <class BufferT, class HttpRequestT, class SerializerT>
  class LogHeroSession : public LogHeroSessionInterface {
    public:
      DISALLOW_COPY_AND_ASSIGN(LogHeroSession);
      LogHeroSession(const LogHeroSettings &settings, const typename BufferT::Settings &bufferSettings);
      virtual ~LogHeroSession();

      // TODO: This method is not thread save
      virtual void submitLogEvent(const LogEvent &logEvent);

    private:
      LogHeroSettings settings;
      BufferT logBuffer;
  };

  template <class BufferT, class HttpRequestT, class SerializerT>
  LogHeroSession<BufferT, HttpRequestT, SerializerT>::LogHeroSession(
    const LogHeroSettings &settings,
    const typename BufferT::Settings &bufferSettings
  ) :
    settings(settings),
    logBuffer(bufferSettings) {
  }

  template <class BufferT, class HttpRequestT, class SerializerT>
  LogHeroSession<BufferT, HttpRequestT, SerializerT>::~LogHeroSession() {
  }

  template <class BufferT, class HttpRequestT, class SerializerT>
  void LogHeroSession<BufferT, HttpRequestT, SerializerT>::submitLogEvent(const LogEvent &logEvent) {
    this->logBuffer.push(logEvent);
    if (this->logBuffer.needsDumping()) {
      loghero::APIAccess<HttpRequestT, SerializerT> apiAccess(this->settings);
      std::unique_ptr<LogEvent::List> pLogEventsToSend = this->logBuffer.dump();
      apiAccess.submitLogEvents(*pLogEventsToSend);
    }
  }

  typedef LogBuffer<LogContainerPolicyInMemory, TimerPolicyCTime> DefaultLogBuffer;
  typedef LogHeroSession<DefaultLogBuffer, HttpRequestCurl, LogEventSerializerJson> LogHeroDefaultSession;
}

#endif // LOGHEROSESSION_H
