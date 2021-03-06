#include "LibLogHero.h"

#include <string>
#include <iostream>

#include "LogHeroSingleton.h"
#include "Logging.h"

#include "LogEventSerializerJson.h"
#include "APIAccess.h"
#include "HttpRequestCurl.h"


void loghero_submitLogEvent(const char *apiKey, struct LogEvent *pLogEvent) {
  std::string apiKeyAsString(apiKey);
  if (apiKeyAsString.empty()) {
    loghero::Log::warning("API key is not set! Submit cancelled!");
    return;
  }
  const loghero::LogEvent logEvent(*pLogEvent);
  loghero::LogHeroSingleton::Instance().submitLogEvent(apiKeyAsString, logEvent);
}

#ifdef LH_ENABLE_LOGGING
void loghero_enableLogging(const char *logDirectory, const char *logLevel) {
  loghero::LogHeroSingleton::Instance().enableLogging(logDirectory, logLevel);
}
#endif // LH_ENABLE_LOGGING
