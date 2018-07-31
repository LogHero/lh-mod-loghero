#include "LogEventSerializerJson.h"

#include <json/json.h>
#include <sstream>


namespace loghero {

  LogEventSerializerJson::LogEventSerializerJson() :
  pColumnsValue(new Json::Value),
  pStreamWriter(std::move(LogEventSerializerJson::createStreamWriter())) {
    this->pColumnsValue->append("cid");
    this->pColumnsValue->append("ip");
    this->pColumnsValue->append("hostname");
    this->pColumnsValue->append("landingPage");
    this->pColumnsValue->append("method");
    this->pColumnsValue->append("statusCode");
    this->pColumnsValue->append("timesamp");
    this->pColumnsValue->append("pageLoadTime");
    this->pColumnsValue->append("ua");
    this->pColumnsValue->append("referer");
  }

  LogEventSerializerJson::~LogEventSerializerJson() {
  }

  std::string LogEventSerializerJson::serialize(const LogEvent::List &logEventList) const {
    Json::Value root;
    root["columns"] = *this->pColumnsValue;
    Json::Value rows;
    for (LogEvent logEvent: logEventList) {
      rows.append(LogEventSerializerJson::createRowValue(logEvent));
    }
    root["rows"] = rows;
    std::stringstream strs;
    this->pStreamWriter->write(root, &strs);
    return strs.str();
  }

  Json::Value LogEventSerializerJson::createRowValue(const LogEvent &logEvent) const {
    Json::Value row;
    row.append(logEvent.getCid());
    row.append(logEvent.getIpHash());
    row.append(logEvent.getHostname());
    row.append(logEvent.getLandingPagePath());
    row.append(logEvent.getMethod());
    row.append(logEvent.getStatusCode());
    row.append(logEvent.getTimestampAsString());
    row.append(logEvent.getPageLoadTimeMilliSec());
    row.append(logEvent.getUserAgent());
    row.append(logEvent.getReferer());
    return row;
  }

  std::unique_ptr<Json::StreamWriter> LogEventSerializerJson::createStreamWriter() {
    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["indentation"] = "";
    return std::unique_ptr<Json::StreamWriter>(writerBuilder.newStreamWriter());
  }

}
