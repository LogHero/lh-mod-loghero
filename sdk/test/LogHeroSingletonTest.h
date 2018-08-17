#ifndef LOGHEROSINGLETONTEST_H
#define LOGHEROSINGLETONTEST_H

#include "LogHeroSettings.h"
#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogHeroSingletonTest : public ::testing::Test {
    public:
      LogHeroSingletonTest();
      virtual ~LogHeroSingletonTest();
      virtual void TearDown();

      LogHeroSettings settings;
  };

}
}

#endif // LOGHEROSINGLETONTEST_H
