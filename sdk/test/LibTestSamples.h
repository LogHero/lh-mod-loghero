#ifndef LIBTESTSAMPLES_H
#define LIBTESTSAMPLES_H

#include "LibLogHero.h"

namespace loghero {
namespace testing {

  static inline ::LogEvent createCLogEventSample() {
    ::LogEvent cLogEvent;
    cLogEvent.hostname = "www.loghero.io";
    cLogEvent.landingPagePath = "/landing/page/path";
    cLogEvent.ipAddress = "123.45.67.89";
    cLogEvent.timestamp = 1530695457;
    cLogEvent.userAgent = "Google Bot";
    return cLogEvent;
  }

}
}

#endif // LIBTESTSAMPLES_H
