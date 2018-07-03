#include "LibLogHero.h"

#include <string>
#include <iostream>

#include "LogEvent.h"


void submitLogEvent(struct LogEvent *pLogEvent) {
  const loghero::LogEvent logEvent(*pLogEvent);
  std::cout << " ** Lib function was called with "
            << logEvent.getLandingPagePath() << "; "
            << logEvent.getIpAddress() << "; "
            << logEvent.getUserAgent() << "; "
            << logEvent.getHostname() << "; "
            << logEvent.getTimestampAsString() << "; "
            << std::endl;
}
