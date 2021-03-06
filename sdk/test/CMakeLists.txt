
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

add_executable(
    test_loghero_lib
    LibTestMain.cpp
    LogHeroSingletonTest.h
    LogHeroSingletonTest.cpp
    LogHeroSessionTest.h
    LogHeroSessionTest.cpp
    LibTestSamples.h
    LogEventTest.h
    LogEventTest.cpp
    LogEventSerializerJsonTest.h
    LogEventSerializerJsonTest.cpp
    APIAccessTest.h
    APIAccessTest.cpp
    MockHttpRequest.h
    FakeHttpRequest.h
    FakeHttpRequest.cpp
    LogBufferTest.h
    LogBufferTest.cpp
    TimerPolicyMock.h
    TimerPolicyMock.cpp
    TimerPolicyTest.h
    TimerPolicyTest.cpp
    SubmitPolicyMock.h
    SubmitPolicyAsyncTest.h
    SubmitPolicyAsyncTest.cpp
)

target_link_libraries(
    test_loghero_lib
    loghero
    ${GMOCK_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)

add_test(
    NAME test_loghero_lib
    COMMAND test_loghero_lib
)
