#ifndef TIMERPOLICYTEST_H
#define TIMERPOLICYTEST_H

#include "LogHeroSettings.h"
#include "gtest/gtest.h"

namespace loghero {
namespace testing {

  class TimerPolicyTest : public ::testing::Test
  {
    public:
      TimerPolicyTest();

      LogHeroSettings settings;
  };

}}

#endif // TIMERPOLICYTEST_H
