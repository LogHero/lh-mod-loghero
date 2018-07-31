#include "LogEvent.h"

#include <openssl/md5.h>

#include <iomanip>
#include <sstream>
#include <ctime>
#include <cassert>


namespace loghero {

  LogEvent::LogEvent(const ::LogEvent &cLogEvent) :
    landingPagePath(cLogEvent.landingPagePath),
    ipAddress(cLogEvent.ipAddress),
    userAgent(cLogEvent.userAgent),
    hostname(cLogEvent.hostname),
    method(cLogEvent.method),
    timestamp(static_cast<time_t>(cLogEvent.timestamp)),
    timestampAsString(LogEvent::convertUnixTimestampToString(static_cast<time_t>(cLogEvent.timestamp))),
    pageLoadTimeMilliSec(cLogEvent.pageLoadTimeMilliSec),
    cid(LogEvent::md5Digest(std::string(cLogEvent.ipAddress) + std::string(cLogEvent.userAgent))),
    ipHash(LogEvent::md5Digest(std::string(cLogEvent.ipAddress))),
    statusCode(cLogEvent.statusCode) {
  }

  std::string LogEvent::convertUnixTimestampToString(time_t timestamp)
  {
    char mbstr[100];
    std::size_t writtenBytes = std::strftime(mbstr, 100, "%FT%T%z", std::localtime(&timestamp));
    assert(writtenBytes > 0);
    return std::string(mbstr);
  }

  std::string LogEvent::md5Digest(const std::string &input) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), digest);
    std::ostringstream sout;
    sout << std::hex << std::setfill('0');
    for(long long c: digest) {
        sout << std::setw(2) << c;
    }
    return sout.str();
  }

}
