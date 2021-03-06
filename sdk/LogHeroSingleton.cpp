#include "LogHeroSingleton.h"
#include "LogHeroSession.h"
#include "Logging.h"

#include <cassert>


namespace loghero {

  template <class LockingPolicy>
  LogHero<LockingPolicy>::LogHero() {
  }

  template <class LockingPolicy>
  LogHero<LockingPolicy>::~LogHero() {
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::submitLogEvent(const std::string &apiKey, const LogEvent &logEvent) {
    typename LockingPolicy::Lock lock(this->mutex);
    Log::debug("Processing log event URL " + logEvent.getLandingPagePath());
    this->session(apiKey)->submitLogEvent(logEvent);
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::resetSession(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    typename LockingPolicy::Lock lock(this->mutex);
    this->resetSessionInternally(apiKey, std::move(pSession));
  }

  template <class LockingPolicy>
  std::size_t LogHero<LockingPolicy>::getNumberOfSessions() const {
    return this->apiKeySessions.size();
  }

  template <class LockingPolicy>
  void LogHero<LockingPolicy>::clearSessions() {
    typename LockingPolicy::Lock lock(this->mutex);
    this->apiKeySessions.clear();
  }

#ifdef LH_ENABLE_LOGGING
  template <class LockingPolicy>
  void LogHero<LockingPolicy>::enableLogging(const std::string &logDirectory, const std::string &logLevel) {
    Log::init(logDirectory, logLevel);
  }
#endif // LH_ENABLE_LOGGING

  template <class LockingPolicy>
  LogHeroSessionInterface* LogHero<LockingPolicy>::session(const std::string &apiKey) {
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
  void LogHero<LockingPolicy>::resetSessionInternally(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    this->apiKeySessions[apiKey] = std::move(pSession);
  }

  template class LogHero<LockingPolicyLockGuard>;
}

