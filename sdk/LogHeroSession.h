#ifndef LOGHEROSESSION_H
#define LOGHEROSESSION_H

#include "LogHeroSessionInterface.h"

namespace loghero {

  class LogHeroSession : public LogHeroSessionInterface {
    public:
      DISALLOW_COPY_AND_ASSIGN(LogHeroSession);
      LogHeroSession();
      virtual ~LogHeroSession();
  };

}

#endif // LOGHEROSESSION_H
