#ifndef LOGCONTAINERPOLICYINMEMORY_H
#define LOGCONTAINERPOLICYINMEMORY_H

#include "LogEvent.h"
#include "LogHeroSettings.h"

#include <memory>

namespace loghero {

  class LogContainerPolicyInMemory {
    public:

      DISALLOW_COPY_AND_ASSIGN(LogContainerPolicyInMemory);
      virtual ~LogContainerPolicyInMemory(){}

    protected:
      LogContainerPolicyInMemory(const LogHeroSettings &settings);
      void pushLogEvent(const LogEvent &logEvent);
      bool logEventsNeedDumping() const;
      std::unique_ptr<LogEvent::List> dumpLogEvents();

    private:
      uint64_t maxLogEvents;
      std::unique_ptr<LogEvent::List> pLogEventList;
  };

  inline LogContainerPolicyInMemory::LogContainerPolicyInMemory(const LogHeroSettings &settings) :
    maxLogEvents(settings.maxLogEventsInBuffer),
    pLogEventList(new LogEvent::List()) {
  }

  inline void LogContainerPolicyInMemory::pushLogEvent(const LogEvent &logEvent) {
    pLogEventList->push_back(logEvent);
  }

  inline bool LogContainerPolicyInMemory::logEventsNeedDumping() const {
    if (this->pLogEventList->size() >= maxLogEvents) {
      return true;
    }
    return false;
  }

  inline std::unique_ptr<LogEvent::List> LogContainerPolicyInMemory::dumpLogEvents() {
    std::unique_ptr<LogEvent::List> pLogEventListForDumping = std::move(this->pLogEventList);
    this->pLogEventList = std::unique_ptr<LogEvent::List>(new LogEvent::List());
    return pLogEventListForDumping;
  }
}

#endif // LOGCONTAINERPOLICYINMEMORY_H
