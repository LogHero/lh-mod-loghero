#ifndef LOGHEROSESSION_H
#define LOGHEROSESSION_H

#include "LogHeroSessionInterface.h"
#include "LogHeroSettings.h"
#include "LogBuffer.h"
#include "LogContainerPolicyInMemory.h"
#include "TimerPolicyCTime.h"
#include "SubmitPolicyAsync.h"
#include "HttpRequestCurl.h"
#include "LogEventSerializerJson.h"


namespace loghero {

  template <class SubmitPolicy>
  class LogHeroSession : public LogHeroSessionInterface, public SubmitPolicy {
    public:
      DISALLOW_COPY_AND_ASSIGN(LogHeroSession);
      LogHeroSession(const LogHeroSettings &settings);
      virtual ~LogHeroSession();

      virtual void submitLogEvent(const LogEvent &logEvent);

    private:

      typename SubmitPolicy::BufferT logBuffer;
  };

  template <class SubmitPolicy>
  LogHeroSession<SubmitPolicy>::LogHeroSession(const LogHeroSettings &settings) :
    SubmitPolicy(settings),
    logBuffer(settings) {
  }

  template <class SubmitPolicy>
  LogHeroSession<SubmitPolicy>::~LogHeroSession() {
  }

  template <class SubmitPolicy>
  void LogHeroSession<SubmitPolicy>::submitLogEvent(const LogEvent &logEvent) {
    this->logBuffer.push(logEvent);
    if (this->logBuffer.needsDumping()) {
      this->dumpAndSubmit(&(this->logBuffer));
    }
  }

  typedef LogBuffer<LogContainerPolicyInMemory, TimerPolicyCTime> DefaultLogBuffer;
  typedef LogHeroSession<
    SubmitPolicyAsync<DefaultLogBuffer, HttpRequestCurl, LogEventSerializerJson>
  > LogHeroDefaultSession;

}

#endif // LOGHEROSESSION_H
