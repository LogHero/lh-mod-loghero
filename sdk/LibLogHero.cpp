#include "LibLogHero.h"

#include <string>
#include <iostream>

#include "LogEvent.h"
#include "LogEventSerializerJson.h"
#include "APIAccess.h"
#include "HttpRequestCurl.h"


void submitLogEvent(struct LogEvent *pLogEvent) {
  loghero::LogEvent::List logEventList;
  logEventList.push_back(loghero::LogEvent(*pLogEvent));
  loghero::LogEventSerializerJson serializer;
  const std::string payloadAsJson = serializer.serialize(logEventList);
  loghero::LogHeroSettings settings("YOUR_API_KEY", "Apache Module loghero/httpd@0.0.1");
  loghero::APIAccess<loghero::HttpRequestCurl> apiAccess(settings);
  apiAccess.submitLogPackage(payloadAsJson);
}
