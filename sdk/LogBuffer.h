#ifndef LOGBUFFER_H
#define LOGBUFFER_H

#include "LogEvent.h"
#include "LockingPolicyLockGuard.h"
#include "GlobalDefines.h"

#include <memory>


namespace loghero {

  // TODO Unit test to check thread safety
  template <class ContainerPolicy, class LockingPolicy = LockingPolicyLockGuard>
  class LogBuffer : protected LockingPolicy, public ContainerPolicy {
    public:

      DISALLOW_COPY_AND_ASSIGN(LogBuffer);
      LogBuffer(const typename ContainerPolicy::Settings &containerSettings);
      virtual ~LogBuffer();

      void push(const LogEvent &logEvent);
      bool needsDumping() const;
      std::unique_ptr<LogEvent::List> dump();

  };

  template <class ContainerPolicy, class LockingPolicy>
  LogBuffer<ContainerPolicy, LockingPolicy>::LogBuffer(const typename ContainerPolicy::Settings &containerSettings) :
    ContainerPolicy(containerSettings) {
  }

  template <class ContainerPolicy, class LockingPolicy>
  LogBuffer<ContainerPolicy, LockingPolicy>::~LogBuffer() {
  }

  template <class ContainerPolicy, class LockingPolicy>
  void LogBuffer<ContainerPolicy, LockingPolicy>::push(const LogEvent &logEvent) {
    typename LockingPolicy::Lock lock(this->mutex);
    ContainerPolicy::pushLogEvent(logEvent);
  }

  template <class ContainerPolicy, class LockingPolicy>
  std::unique_ptr<LogEvent::List> LogBuffer<ContainerPolicy, LockingPolicy>::dump() {
    typename LockingPolicy::Lock lock(this->mutex);
    return ContainerPolicy::dumpLogEvents();
  }

  template <class ContainerPolicy, class LockingPolicy>
  bool LogBuffer<ContainerPolicy, LockingPolicy>::needsDumping() const {
    typename LockingPolicy::Lock lock(this->mutex);
    return ContainerPolicy::logEventsNeedDumping();
  }

}

#endif // LOGBUFFER_H
