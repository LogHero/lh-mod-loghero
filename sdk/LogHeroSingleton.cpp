#include "LogHeroSingleton.h"
#include "LogHeroSession.h"

#include <cassert>


namespace loghero {

  template <class LockingPolicy>
  LogHero<LockingPolicy>::LogHero() {
  }

  template <class LockingPolicy>
  LogHero<LockingPolicy>::~LogHero() {
  }

  template <class LockingPolicy>
  LogHeroSessionInterface* LogHero<LockingPolicy>::session(const std::string &apiKey) {
    typename LockingPolicy::Lock lock(this->mutex);
    SessionMapT::iterator it = this->apiKeySessions.find(apiKey);
    if (it == this->apiKeySessions.end()) {
      loghero::LogHeroSettings settings(apiKey);
      this->resetSessionInternally(
        apiKey,
        std::unique_ptr<LogHeroSessionInterface>(new LogHeroDefaultSession(settings))
      );
      it = this->apiKeySessions.find(apiKey);
    }
    assert(it != this->apiKeySessions.end());
    return it->second.get();
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::resetSession(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    typename LockingPolicy::Lock lock(this->mutex);
    this->resetSessionInternally(apiKey, std::move(pSession));
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::clearSessions() {
    typename LockingPolicy::Lock lock(this->mutex);
    this->apiKeySessions.clear();
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::resetSessionInternally(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    this->apiKeySessions[apiKey] = std::move(pSession);
  }

  template class LogHero<LockingPolicyLockGuard>;
}

