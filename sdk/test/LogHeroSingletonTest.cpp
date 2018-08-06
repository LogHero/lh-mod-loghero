#include "LogHeroSingletonTest.h"
#include "LogHeroSingleton.h"
#include "LogHeroSession.h"


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
    LogHeroSessionInterface *pCustomSession = new LogHeroDefaultSession(this->settings, DefaultLogBuffer::Settings());
    LogHeroSingleton::Instance().resetSession("KEY_1", std::unique_ptr<LogHeroSessionInterface>(pCustomSession));
    LogHeroSessionInterface *pAccessedCustomSession = LogHeroSingleton::Instance().session("KEY_1");
    ASSERT_NE(pDefaultSession, pAccessedCustomSession);
    ASSERT_EQ(pCustomSession, pAccessedCustomSession);
  }

}
}
