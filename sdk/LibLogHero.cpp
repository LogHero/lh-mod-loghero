#include "LibLogHero.h"

#include <string>
#include <iostream>

#include "LogHeroSingleton.h"

#include "LogEventSerializerJson.h"
#include "APIAccess.h"
#include "HttpRequestCurl.h"


void submitLogEvent(const char *apiKey, struct LogEvent *pLogEvent) {
  std::string apiKeyAsString(apiKey);
  if (apiKeyAsString.empty()) {
    std::cout << "API KEY IS NOT SET!! SUBMIT CANCELLED!!" << apiKey << std::endl;
    return;
  }
  const loghero::LogEvent logEvent(*pLogEvent);
  loghero::LogHeroSingleton::Instance().submitLogEvent(apiKeyAsString, logEvent);
}
