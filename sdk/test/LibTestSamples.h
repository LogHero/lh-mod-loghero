#ifndef LIBTESTSAMPLES_H
#define LIBTESTSAMPLES_H

#include "LibLogHero.h"
#include "LogEvent.h"


namespace loghero {
namespace testing {

  static inline time_t createSampleTimestamp() {
    return 1530695457;
  }

  static inline ::LogEvent createCLogEventSample() {
    ::LogEvent cLogEvent;
    cLogEvent.hostname = "www.loghero.io";
    cLogEvent.landingPagePath = "/landing/page/path";
    cLogEvent.ipAddress = "123.45.67.89";
    cLogEvent.timestamp = createSampleTimestamp();
    cLogEvent.userAgent = "Google Bot";
    return cLogEvent;
  }

  static inline std::string createSampleTimestampAsString() {
    return LogEvent::convertUnixTimestampToString(createSampleTimestamp());
  }

}
}

#endif // LIBTESTSAMPLES_H
