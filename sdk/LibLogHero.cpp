#include "LibLogHero.h"
#include "LogEvent.h"
#include <iostream>
#include <string>


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
