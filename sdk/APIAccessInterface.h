#ifndef APIACCESSINTERFACE_H
#define APIACCESSINTERFACE_H

#include "GlobalDefines.h"

#include <string>

namespace loghero {

    class APIAccessInterface {
      public:

        DISALLOW_COPY_AND_ASSIGN(APIAccessInterface);
        APIAccessInterface(){}
        virtual ~APIAccessInterface(){}

        virtual void submitLogPackage(const std::string &payloadAsJson) const = 0;

    };

}

#endif // APIACCESSINTERFACE_H
