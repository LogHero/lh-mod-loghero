#ifndef LOGEVENTSERIALIZERJSON_H
#define LOGEVENTSERIALIZERJSON_H

#include "GlobalDefines.h"
#include "LogEventSerializerInterface.h"


#include <memory>


namespace Json {
  class Value;
}

namespace loghero {

  class LogEventSerializerJson : public LogEventSerializerInterface {
    public:

      LogEventSerializerJson();
      virtual ~LogEventSerializerJson();

      virtual std::string serialize(const LogEvent::List &logEventList) const;

    private:

      std::unique_ptr<Json::Value> pColumnsValue;

  };

}

#endif // LOGEVENTSERIALIZERJSON_H
