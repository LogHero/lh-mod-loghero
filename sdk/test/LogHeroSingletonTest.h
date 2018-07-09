#ifndef LOGHEROSINGLETONTEST_H
#define LOGHEROSINGLETONTEST_H

#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogHeroSingletonTest : public ::testing::Test
  {
    public:
      LogHeroSingletonTest();
      virtual ~LogHeroSingletonTest();
      virtual void TearDown();
  };

}
}

#endif // LOGHEROSINGLETONTEST_H
