#ifndef LOGCONTAINERPOLICYINMEMORY_H
#define LOGCONTAINERPOLICYINMEMORY_H

#include "LogEvent.h"

#include <memory>

namespace loghero {

  class LogContainerPolicyInMemory {
    public:
      virtual ~LogContainerPolicyInMemory(){}

      struct Settings {
        explicit Settings(uint64_t maxLogEvents = 500) :
          maxLogEvents(maxLogEvents) {
        }
        uint64_t maxLogEvents;
      };

    protected:
      LogContainerPolicyInMemory(const Settings &settings);
      void pushLogEvent(const LogEvent &logEvent);
      bool logEventsNeedDumping() const;
      std::unique_ptr<LogEvent::List> dumpLogEvents();

    private:
      Settings settings;
      std::unique_ptr<LogEvent::List> pLogEventList;
  };

  inline LogContainerPolicyInMemory::LogContainerPolicyInMemory(const Settings &settings) :
    settings(settings),
    pLogEventList(new LogEvent::List()) {
  }

  inline void LogContainerPolicyInMemory::pushLogEvent(const LogEvent &logEvent) {
    pLogEventList->push_back(logEvent);
  }

  inline bool LogContainerPolicyInMemory::logEventsNeedDumping() const {
    if (this->pLogEventList->size() >= this->settings.maxLogEvents) {
      return true;
    }
    return false;
  }

  inline std::unique_ptr<LogEvent::List> LogContainerPolicyInMemory::dumpLogEvents() {
    std::unique_ptr<LogEvent::List> pLogEventListForDumping = std::move(this->pLogEventList);
    pLogEventList = std::unique_ptr<LogEvent::List>(new LogEvent::List());
    return std::move(pLogEventListForDumping);
  }
}

#endif // LOGCONTAINERPOLICYINMEMORY_H
