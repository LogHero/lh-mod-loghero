#include "LibLogHero.h"

#include <string>
#include <iostream>

#include "LogHeroSingleton.h"

#include "LogEventSerializerJson.h"
#include "APIAccess.h"
#include "HttpRequestCurl.h"


void submitLogEvent(struct LogEvent *pLogEvent) {
  loghero::LogHeroSingleton::Instance().session("YOUR_API_KEY")->submitLogEvent(loghero::LogEvent(*pLogEvent));
}
