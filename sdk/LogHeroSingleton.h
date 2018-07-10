#ifndef LOGHEROSINGLETON_H
#define LOGHEROSINGLETON_H

#include "LogHeroSessionInterface.h"
#include "loki/Singleton.h"

#include <map>
#include <string>
#include <mutex>
#include <memory>


namespace loghero {

  class LogHero {
    public:

      LogHeroSessionInterface* session(const std::string &apiKey);

      void resetSession(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession);

      void clearSessions();

    private:
      friend struct Loki::CreateUsingNew<LogHero>;

      LogHero();
      ~LogHero();

      typedef std::map<std::string, std::unique_ptr<LogHeroSessionInterface> > SessionMapT;

      void resetSessionInternally(const std::string &apiKey, std::unique_ptr<LogHeroSessionInterface> pSession);

      std::mutex mutex;
      SessionMapT apiKeySessions;
  };

  typedef Loki::SingletonHolder<LogHero> LogHeroSingleton;

}


#endif // LOGHEROSINGLETON_H
