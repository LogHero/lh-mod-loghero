#ifndef LOGHEROSETTINGS_H
#define LOGHEROSETTINGS_H

#include <string>

namespace loghero {

  struct LogHeroSettings {

    LogHeroSettings(const std::string &apiKey):
    apiEndpoint("https://test.loghero.io/logs/"),
    apiKey(apiKey) {
    }

    std::string apiEndpoint;
    std::string apiKey;
  };

}

#endif // LOGHEROSETTINGS_H
