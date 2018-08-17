#ifndef SUBMITPOLICYASYNCTEST_H
#define SUBMITPOLICYASYNCTEST_H

#include "LogHeroSettings.h"

#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class SubmitPolicyAsyncTest : public ::testing::Test
  {
    public:
      SubmitPolicyAsyncTest();

      LogHeroSettings settings;
  };

}}

#endif // SUBMITPOLICYASYNCTEST_H
