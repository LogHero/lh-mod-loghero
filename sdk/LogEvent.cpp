#include "LogEvent.h"

#include <iostream>
#include <sstream>
#include <ctime>

namespace loghero {

  LogEvent::LogEvent(const ::LogEvent &cLogEvent)
    : landingPagePath(cLogEvent.landingPagePath),
      ipAddress(cLogEvent.ipAddress),
      userAgent(cLogEvent.userAgent),
      hostname(cLogEvent.hostname),
      timestamp(static_cast<time_t>(cLogEvent.timestamp)),
      timestampAsString(
        LogEvent::convertUnixTimestampToString(static_cast<time_t>(cLogEvent.timestamp))
      )
  {
  }

  std::string LogEvent::convertUnixTimestampToString(time_t timestamp)
  {
    // TODO: Use http://php.net/manual/de/function.strftime.php
    char mbstr[100];
    if (std::strftime(mbstr, 100, "%FT%T%z", std::localtime(&timestamp))) {
        return std::string(mbstr);
    }
    throw std::string("TODO!!");
  }

}
