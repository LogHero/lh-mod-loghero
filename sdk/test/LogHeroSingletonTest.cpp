#include "LogHeroSingletonTest.h"
#include "LogHeroSingleton.h"
#include "LogHeroSession.h"
#include "SubmitPolicyMock.h"
#include "LibTestSamples.h"

#include <boost/asio.hpp>
#include <experimental/random>


namespace loghero {
namespace testing {

  LogHeroSingletonTest::LogHeroSingletonTest():
    settings("SOME_API_KEY") {
  }

  LogHeroSingletonTest::~LogHeroSingletonTest() {
  }

  void LogHeroSingletonTest::TearDown() {
    LogHeroSingleton::Instance().clearSessions();
  }

  TEST_F(LogHeroSingletonTest, InitializeDefaultSessionPerAPIKey) {
    ASSERT_EQ(LogHeroSingleton::Instance().getNumberOfSessions(), std::size_t(0));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    ASSERT_EQ(LogHeroSingleton::Instance().getNumberOfSessions(), std::size_t(1));
    LogHeroSingleton::Instance().submitLogEvent("KEY_2", LogEvent(createCLogEventSample()));
    ASSERT_EQ(LogHeroSingleton::Instance().getNumberOfSessions(), std::size_t(2));
  }

  TEST_F(LogHeroSingletonTest, SubmitLogEvent) {
    this->settings.maxLogEventsInBuffer = 3;
    LogHeroSession<SubmitPolicyMock> *pCustomSession = new LogHeroSession<SubmitPolicyMock>(this->settings);
    LogHeroSingleton::Instance().resetSession("KEY_1", std::unique_ptr<LogHeroSessionInterface>(pCustomSession));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    ASSERT_EQ(pCustomSession->getNumberOfDumpedLogEvents(), std::size_t(3));
    LogHeroSingleton::Instance().submitLogEvent("KEY_1", LogEvent(createCLogEventSample()));
    ASSERT_EQ(pCustomSession->getNumberOfDumpedLogEvents(), std::size_t(6));
  }

  TEST_F(LogHeroSingletonTest, IsThreadSafe) {
    unsigned int numberOfThreads = 20;
    unsigned int numberOfTasks = 300;
    ASSERT_LT(numberOfTasks, LogHeroSettings("").maxLogEventsInBuffer);
    std::vector<std::string> apiKeys(3);
    std::generate(apiKeys.begin(), apiKeys.end(), [n = 0] () mutable {
      std::stringstream strs;
      strs << "KEY_" << ++n;
      return strs.str();
    });
    auto task = [=]() {
      std::size_t keyIdx = std::experimental::randint(std::size_t(0), apiKeys.size() - 1);
      const std::string &apiKey = apiKeys[keyIdx];
      LogHeroSingleton::Instance().submitLogEvent(apiKey, LogEvent(createCLogEventSample()));
      LogHeroSingleton::Instance().resetSession(
            apiKey,
            std::unique_ptr<LogHeroSessionInterface>(new LogHeroDefaultSession(this->settings))
          );
      LogHeroSingleton::Instance().clearSessions();
    };
    boost::asio::thread_pool threadPool(numberOfThreads);
    for (unsigned int i=0; i<numberOfTasks; ++i) {
      boost::asio::post(threadPool, task);
    }
    threadPool.join();
  }

}
}
