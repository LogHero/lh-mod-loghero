#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "LibLogHero.h"

#include <string>

#include "GlobalDefines.h"

namespace loghero {
  class LogEvent {

    public:
      LogEvent(const ::LogEvent &cLogEvent);

      const inline std::string& getLandingPagePath() const {
        return this->landingPagePath;
      }

      const inline std::string& getIpAddress() const {
        return this->ipAddress;
      }

      const inline std::string& getUserAgent() const {
        return this->userAgent;
      }

      const inline std::string& getHostname() const {
        return this->hostname;
      }

      const inline time_t getTimestamp() const {
        return this->timestamp;
      }

      const inline std::string& getTimestampAsString() const {
        return this->timestampAsString;
      }

    private:

      static std::string convertUnixTimestampToString(time_t timestamp);

      const std::string landingPagePath;
      const std::string ipAddress;
      const std::string userAgent;
      const std::string hostname;
      const time_t timestamp;
      const std::string timestampAsString;

  };
}

#endif // LOGEVENT_H
