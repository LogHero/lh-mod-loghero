#ifndef LOGHEROSETTINGS_H
#define LOGHEROSETTINGS_H

#include "GlobalDefines.h"
#include <string>

namespace loghero {

  struct LogHeroSettings {

    LogHeroSettings(const std::string &apiKey):
      apiEndpoint("https://test.loghero.io/logs/"),
      apiKey(apiKey),
      maxLogEventsInBuffer(500),
      logBufferTimeoutSeconds(300) {
    }

    std::string apiEndpoint;
    std::string apiKey;
    uint64_t maxLogEventsInBuffer;
    uint64_t logBufferTimeoutSeconds;
  };

}

#endif // LOGHEROSETTINGS_H
