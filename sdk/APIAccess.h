#ifndef APIACCESS_H
#define APIACCESS_H


#include "APIAccessInterface.h"


namespace loghero {

  class APIAccess : public APIAccessInterface
  {
    public:
      APIAccess();
      virtual ~APIAccess();

      virtual void submitLogPackage(const std::string &payloadAsJson) const;

  };

}

#endif // APIACCESS_H
