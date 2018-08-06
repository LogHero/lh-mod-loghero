#include "LogBufferTest.h"
#include "LogBuffer.h"
#include "LibTestSamples.h"


namespace loghero {
namespace testing {

  LogBufferTest::LogBufferTest():
    containerSettings(5) {
  }

  TEST_F(LogBufferTest, CollectAndDumpLogEvents) {
    LogBuffer<LogContainerPolicyInMemory> logBuffer(this->containerSettings);
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    std::unique_ptr<LogEvent::List> pDumpedEvents = logBuffer.dump();
    ASSERT_EQ(pDumpedEvents->size(), std::size_t(3));
    std::unique_ptr<LogEvent::List> pDumpedEvents2 = logBuffer.dump();
    ASSERT_EQ(pDumpedEvents2->size(), std::size_t(0));
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    std::unique_ptr<LogEvent::List> pDumpedEvents3 = logBuffer.dump();
    ASSERT_EQ(pDumpedEvents3->size(), std::size_t(2));
  }

  TEST_F(LogBufferTest, NeedsDumping) {
    LogBuffer<LogContainerPolicyInMemory> logBuffer(this->containerSettings);
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    ASSERT_FALSE(logBuffer.needsDumping());
    logBuffer.push(LogEvent(createCLogEventSample()));
    logBuffer.push(LogEvent(createCLogEventSample()));
    ASSERT_TRUE(logBuffer.needsDumping());
    logBuffer.dump();
    ASSERT_FALSE(logBuffer.needsDumping());
  }


}}
