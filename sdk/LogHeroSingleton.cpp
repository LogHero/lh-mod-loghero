#include "LogHeroSingleton.h"
#include "LogHeroSession.h"

#include <cassert>


namespace loghero {

  LogHero::LogHero() {
  }

  LogHero::~LogHero() {
  }

  LogHeroSessionInterface* LogHero::session(const std::string &apiKey) {
    std::lock_guard<std::mutex> lock(this->mutex);
    SessionMapT::iterator it = this->apiKeySessions.find(apiKey);
    if (it == this->apiKeySessions.end()) {
      this->resetSessionInternally(apiKey, std::unique_ptr<LogHeroSessionInterface>(new LogHeroSession()));
      it = this->apiKeySessions.find(apiKey);
    }
    assert(it != this->apiKeySessions.end());
    return it->second.get();
  }

  void LogHero::resetSession(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->resetSessionInternally(apiKey, std::move(pSession));
  }

  void LogHero::clearSessions() {
    std::lock_guard<std::mutex> lock(this->mutex);
    this->apiKeySessions.clear();
  }

  void LogHero::resetSessionInternally(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession) {
    this->apiKeySessions[apiKey] = std::move(pSession);
  }


}

