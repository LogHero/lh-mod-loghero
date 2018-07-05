#ifndef LOGEVENTSERIALIZERJSON_H
#define LOGEVENTSERIALIZERJSON_H

#include "GlobalDefines.h"
#include "LogEventSerializerInterface.h"

#include <memory>


namespace Json {
  class Value;
  class StreamWriter;
}

namespace loghero {

  class LogEventSerializerJson : public LogEventSerializerInterface {
    public:

      LogEventSerializerJson();
      virtual ~LogEventSerializerJson();

      virtual std::string serialize(const LogEvent::List &logEventList) const;

    private:

      Json::Value createRowValue(const LogEvent &logEvent) const;

      static std::unique_ptr<Json::StreamWriter> createStreamWriter();

      std::unique_ptr<Json::Value> pColumnsValue;
      std::unique_ptr<Json::StreamWriter> pStreamWriter;

  };

}

#endif // LOGEVENTSERIALIZERJSON_H
