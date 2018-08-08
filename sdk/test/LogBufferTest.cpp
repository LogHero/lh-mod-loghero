#include "LogBufferTest.h"
#include "LogBuffer.h"
#include "LibTestSamples.h"


namespace loghero {
namespace testing {

  LogBufferTest::LogBufferTest():
    settings("SOME_API_KEY") {
    TimerPolicyMock::resetMockInstance(&timerMock);
    settings.maxLogEventsInBuffer = 5;
  }

  TEST_F(LogBufferTest, InitializeTimerInConstructor) {
    EXPECT_CALL(this->timerMock, mockedReset());
    LogBuffer<LogContainerPolicyInMemory, TimerPolicyMock> logBuffer(this->settings);
  }

  TEST_F(LogBufferTest, CollectAndDumpLogEvents) {
    EXPECT_CALL(this->timerMock, mockedReset()).Times(4);
    LogBuffer<LogContainerPolicyInMemory, TimerPolicyMock> logBuffer(this->settings);
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

  TEST_F(LogBufferTest, NeedsDumpingIfMaximumBufferSizeReached) {
    EXPECT_CALL(this->timerMock, mockedReset()).Times(2);
    LogBuffer<LogContainerPolicyInMemory, TimerPolicyMock> logBuffer(this->settings);
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

  TEST_F(LogBufferTest, NeedsDumpingIfMaximumTimeIntervalReached) {
    EXPECT_CALL(this->timerMock, mockedReset());
    LogBuffer<LogContainerPolicyInMemory, TimerPolicyMock> logBuffer(this->settings);
    logBuffer.push(LogEvent(createCLogEventSample()));
    ASSERT_FALSE(logBuffer.needsDumping());
    timerMock.setTimeElapsedSeconds(60);
    ASSERT_TRUE(logBuffer.needsDumping());
  }

}}
