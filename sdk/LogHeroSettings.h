#ifndef LOGHEROSETTINGS_H
#define LOGHEROSETTINGS_H

#include <string>

namespace loghero {

  struct LogHeroSettings {

    LogHeroSettings(const std::string &apiKey, const std::string &clientId):
    apiEndpoint("https://test.loghero.io/logs/"),
    apiKey(apiKey),
    clientId(clientId) {
    }

    std::string apiEndpoint;
    std::string apiKey;
    std::string clientId;
  };

}

#endif // LOGHEROSETTINGS_H
