#ifndef LOGEVENTSERIALIZERINTERFACE_H
#define LOGEVENTSERIALIZERINTERFACE_H

#include "GlobalDefines.h"
#include "LogEvent.h"

namespace loghero {

  class LogEventSerializerInterface {
    public:

      DISALLOW_COPY_AND_ASSIGN(LogEventSerializerInterface);
      LogEventSerializerInterface(){}
      virtual ~LogEventSerializerInterface(){}

      virtual std::string serialize(const LogEvent::List &logEventList) const = 0;

  };

}

#endif // LOGEVENTSERIALIZERINTERFACE_H
