#ifndef LOGBUFFERTEST_H
#define LOGBUFFERTEST_H

#include "LogContainerPolicyInMemory.h"
#include "gtest/gtest.h"


namespace loghero {
namespace testing {

  class LogBufferTest : public ::testing::Test {
    public:
      LogBufferTest();

      LogContainerPolicyInMemory::Settings containerSettings;
  };

}}

#endif // LOGBUFFERTEST_H
