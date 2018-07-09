#ifndef LOGHEROSESSIONINTERFACE_H
#define LOGHEROSESSIONINTERFACE_H

#include "GlobalDefines.h"


namespace loghero {

    class LogHeroSessionInterface {
      public:
        DISALLOW_COPY_AND_ASSIGN(LogHeroSessionInterface);
        LogHeroSessionInterface(){}
        virtual ~LogHeroSessionInterface(){}
    };

}

#endif // LOGHEROSESSIONINTERFACE_H
