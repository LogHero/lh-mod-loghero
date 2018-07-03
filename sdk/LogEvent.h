#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "LibLogHero.h"
#include "GlobalDefines.h"
#include <string>

namespace loghero {
  class LogEvent {

    public:
      LogEvent(const ::LogEvent &cLogEvent)
        : landingPagePath(cLogEvent.landingPagePath),
          ipAddress(cLogEvent.ipAddress),
          userAgent(cLogEvent.userAgent),
          hostname(cLogEvent.hostname),
          timestamp(static_cast<int64>(cLogEvent.timestamp))
      {

      }

      const std::string& getLandingPagePath() const {
        return this->landingPagePath;
      }

      const std::string& getIpAddress() const {
        return this->ipAddress;
      }

      const std::string& getUserAgent() const {
        return this->userAgent;
      }

      const std::string& getHostname() const {
        return this->hostname;
      }

      const int64 getTimestamp() const {
        return this->timestamp;
      }

    private:
      const std::string landingPagePath;
      const std::string ipAddress;
      const std::string userAgent;
      const std::string hostname;
      const int64 timestamp;

  };
}

#endif // LOGEVENT_H
