#ifndef LOGEVENT_H
#define LOGEVENT_H

#include "LibLogHero.h"

#include <string>
#include <vector>

#include "GlobalDefines.h"

namespace loghero {
  class LogEvent {
    public:

      typedef std::vector<LogEvent> List;

      LogEvent(const ::LogEvent &cLogEvent);

      const inline std::string& getLandingPagePath() const {
        return this->landingPagePath;
      }

      const inline std::string& getIpAddress() const {
        return this->ipAddress;
      }

      const inline std::string& getIpHash() const {
        return this->ipHash;
      }

      const inline std::string& getUserAgent() const {
        return this->userAgent;
      }

      const inline std::string& getCid() const {
        return this->cid;
      }

      const inline std::string& getHostname() const {
        return this->hostname;
      }

      const inline std::string& getMethod() const {
        return this->method;
      }

      const inline int getStatusCode() const {
        return this->statusCode;
      }

      const inline time_t getTimestamp() const {
        return this->timestamp;
      }

      const inline std::string& getTimestampAsString() const {
        return this->timestampAsString;
      }

      static std::string convertUnixTimestampToString(time_t timestamp);

    private:

      static std::string createCidFromIpAndUserAgent(const std::string &ipAddress, const std::string &userAgent);

      static std::string md5Digest(const std::string &input);

      const std::string landingPagePath;
      const std::string ipAddress;
      const std::string userAgent;
      const std::string hostname;
      const std::string method;
      const time_t timestamp;
      const std::string timestampAsString;
      const std::string cid;
      const std::string ipHash;
      const int statusCode;

  };
}

#endif // LOGEVENT_H
