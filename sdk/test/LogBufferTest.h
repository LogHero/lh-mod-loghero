#ifndef LOGBUFFERTEST_H
#define LOGBUFFERTEST_H

#include "LogContainerPolicyInMemory.h"
#include "TimerPolicyMock.h"
#include "LogHeroSettings.h"
#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogBufferTest : public ::testing::Test {
    public:
      LogBufferTest();

      LogHeroSettings settings;

      TimerPolicyMock timerMock;
  };

}}

#endif // LOGBUFFERTEST_H
