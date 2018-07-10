#ifndef LOGHEROSESSIONINTERFACE_H
#define LOGHEROSESSIONINTERFACE_H

#include "LogEvent.h"
#include "GlobalDefines.h"


namespace loghero {

    class LogHeroSessionInterface {
      public:
        DISALLOW_COPY_AND_ASSIGN(LogHeroSessionInterface);
        LogHeroSessionInterface(){}
        virtual ~LogHeroSessionInterface(){}

        virtual void submitLogEvent(const LogEvent &logEvent) = 0;

    };

}

#endif // LOGHEROSESSIONINTERFACE_H
