#include "LogEvent.h"

#include <boost/algorithm/string.hpp>
#include <openssl/md5.h>

#include <iomanip>
#include <sstream>
#include <ctime>
#include <cassert>
#include <vector>


namespace loghero {

  LogEvent::LogEvent(const ::LogEvent &cLogEvent) :
    landingPagePath(LogEvent::setStringValue(cLogEvent.landingPagePath)),
    ipAddress(LogEvent::setStringValue(cLogEvent.ipAddress)),
    userAgent(LogEvent::setStringValue(cLogEvent.userAgent)),
    hostname(LogEvent::setStringValue(cLogEvent.hostname)),
    method(LogEvent::setStringValue(cLogEvent.method)),
    referer(LogEvent::setStringValue(cLogEvent.referer)),
    timestamp(static_cast<time_t>(cLogEvent.timestamp)),
    timestampAsString(LogEvent::convertUnixTimestampToString(static_cast<time_t>(cLogEvent.timestamp))),
    pageLoadTimeMilliSec(cLogEvent.pageLoadTimeMilliSec),
    cid(LogEvent::md5Digest(LogEvent::setStringValue(cLogEvent.ipAddress) + LogEvent::setStringValue(cLogEvent.userAgent))),
    ipHash(LogEvent::md5Digest(LogEvent::setStringValue(cLogEvent.ipAddress))),
    ipGroupHashes(LogEvent::createIpGroupHashes(LogEvent::setStringValue(cLogEvent.ipAddress))),
    statusCode(cLogEvent.statusCode) {
  }

  std::string LogEvent::convertUnixTimestampToString(time_t timestamp) {
    char mbstr[100];
    std::size_t writtenBytes = std::strftime(mbstr, 100, "%FT%T%z", std::localtime(&timestamp));
    assert(writtenBytes > 0);
    return std::string(mbstr);
  }

  std::string LogEvent::createIpGroupHashes(const std::string &ipAddress) {
    if(ipAddress.empty()) {
      return "";
    }
    std::vector<std::string> ipGroups;
    boost::split(ipGroups, ipAddress, boost::is_any_of("."));
    for (unsigned int i=0; i<ipGroups.size(); ++i) {
      ipGroups[i] = LogEvent::md5Digest(ipGroups[i]);
    }
    return boost::algorithm::join(ipGroups, ".");
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

  std::string LogEvent::setStringValue(const char *cValue) {
    return cValue ? cValue : "";
  }

}
