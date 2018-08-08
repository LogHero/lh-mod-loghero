#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#include "LogEvent.h"
#include "LogHeroSettings.h"
#include "LockingPolicyLockGuard.h"
#include "GlobalDefines.h"

#include <memory>


namespace loghero {

  // TODO Unit test to check thread safety
  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy = LockingPolicyLockGuard>
  class LogBuffer : protected LockingPolicy, TimerPolicy, public ContainerPolicy {
    public:

      DISALLOW_COPY_AND_ASSIGN(LogBuffer);
      LogBuffer(const LogHeroSettings &settings);
      virtual ~LogBuffer();

      void push(const LogEvent &logEvent);
      bool needsDumping() const;
      std::unique_ptr<LogEvent::List> dump();

  };

  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy>
  LogBuffer<ContainerPolicy, TimerPolicy, LockingPolicy>::LogBuffer(const LogHeroSettings &settings) :
    TimerPolicy(settings),
    ContainerPolicy(settings) {
    TimerPolicy::reset();
  }

  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy>
  LogBuffer<ContainerPolicy, TimerPolicy, LockingPolicy>::~LogBuffer() {
  }

  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy>
  void LogBuffer<ContainerPolicy, TimerPolicy, LockingPolicy>::push(const LogEvent &logEvent) {
    typename LockingPolicy::Lock lock(this->mutex);
    ContainerPolicy::pushLogEvent(logEvent);
  }

  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy>
  std::unique_ptr<LogEvent::List> LogBuffer<ContainerPolicy, TimerPolicy, LockingPolicy>::dump() {
    typename LockingPolicy::Lock lock(this->mutex);
    std::unique_ptr<LogEvent::List> pLogEvents = ContainerPolicy::dumpLogEvents();
    TimerPolicy::reset();
    return pLogEvents;
  }

  template <class ContainerPolicy, class TimerPolicy, class LockingPolicy>
  bool LogBuffer<ContainerPolicy, TimerPolicy, LockingPolicy>::needsDumping() const {
    typename LockingPolicy::Lock lock(this->mutex);
    return ContainerPolicy::logEventsNeedDumping() || TimerPolicy::timeout();
  }

}

#endif // LOGBUFFER_H
