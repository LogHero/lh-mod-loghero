#include "LogHeroSingletonTest.h"
#include "LogHeroSingleton.h"
#include "LogHeroSession.h"

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
    LogHeroSessionInterface *pSessionForApiKey1FirstAccess = LogHeroSingleton::Instance().session("KEY_1");
    LogHeroSessionInterface *pSessionForApiKey1SecondAccess = LogHeroSingleton::Instance().session("KEY_1");
    ASSERT_TRUE(pSessionForApiKey1FirstAccess != NULL);
    ASSERT_EQ(pSessionForApiKey1FirstAccess, pSessionForApiKey1SecondAccess);
    LogHeroSessionInterface *pSessionForApiKey2 = LogHeroSingleton::Instance().session("KEY_2");
    ASSERT_NE(pSessionForApiKey1FirstAccess, pSessionForApiKey2);
  }

  TEST_F(LogHeroSingletonTest, SetCustomSession) {
    LogHeroSessionInterface *pDefaultSession = LogHeroSingleton::Instance().session("KEY_1");
    LogHeroSessionInterface *pCustomSession = new LogHeroDefaultSession(this->settings);
    LogHeroSingleton::Instance().resetSession("KEY_1", std::unique_ptr<LogHeroSessionInterface>(pCustomSession));
    LogHeroSessionInterface *pAccessedCustomSession = LogHeroSingleton::Instance().session("KEY_1");
    ASSERT_NE(pDefaultSession, pAccessedCustomSession);
    ASSERT_EQ(pCustomSession, pAccessedCustomSession);
  }

  TEST_F(LogHeroSingletonTest, IsThreadSafe) {
    unsigned int numberOfThreads = 20;
    unsigned int numberOfTasks = 2000;
    std::vector<std::string> apiKeys(3);
    std::generate(apiKeys.begin(), apiKeys.end(), [n = 0] () mutable {
      std::stringstream strs;
      strs << "KEY_" << ++n;
      return strs.str();
    });
    auto task = [=]() {
      std::size_t keyIdx = std::experimental::randint(std::size_t(0), apiKeys.size() - 1);
      const std::string &apiKey = apiKeys[keyIdx];
      LogHeroSingleton::Instance().session(apiKey);
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
