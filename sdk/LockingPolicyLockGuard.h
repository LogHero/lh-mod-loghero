#ifndef LOCKINGPOLICYLOCKGUARD_H
#define LOCKINGPOLICYLOCKGUARD_H

#include <mutex>

namespace loghero {

  class LockingPolicyLockGuard {
    public:

      virtual ~LockingPolicyLockGuard(){}

      typedef std::lock_guard<std::mutex> Lock;

    protected:
      mutable std::mutex mutex;
  };
}

#endif // LOCKINGPOLICYLOCKGUARD_H
