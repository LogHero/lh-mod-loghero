#include "LogEventSerializerJson.h"

#include <json/json.h>
#include <sstream>


namespace loghero {

  LogEventSerializerJson::LogEventSerializerJson() :
  pColumnsValue(new Json::Value) {
    this->pColumnsValue->append("hostname");
    this->pColumnsValue->append("landingPage");
    this->pColumnsValue->append("timesamp");
    this->pColumnsValue->append("ua");
  }

  LogEventSerializerJson::~LogEventSerializerJson() {
  }

  std::string LogEventSerializerJson::serialize(const LogEvent::List &logEventList) const {
    Json::Value root;
    root["columns"] = *this->pColumnsValue;
    std::stringstream strs;
    Json::StreamWriterBuilder writerBuilder;
    writerBuilder["indentation"] = "";
    std::unique_ptr<Json::StreamWriter> pWriter(writerBuilder.newStreamWriter());
    pWriter->write(root, &strs);
    return strs.str();
  }

}

