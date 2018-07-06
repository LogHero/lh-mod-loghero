#ifndef APIACCESSTEST_H
#define APIACCESSTEST_H

#include "LogHeroSettings.h"

#include "gtest/gtest.h"

namespace loghero {
namespace testing {

  class APIAccessTest : public ::testing::Test {
    public:

      APIAccessTest();
      virtual ~APIAccessTest();

      LogHeroSettings logHeroSettings;

  };

}
}

#endif // APIACCESSTEST_H
