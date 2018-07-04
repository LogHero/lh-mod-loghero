
find_package(GTest REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
)

add_executable(
    test_loghero_lib
    LibTestMain.cpp
    LibTestSamples.h
    LogEventTest.h
    LogEventTest.cpp
    LogEventSerializerJsonTest.h
    LogEventSerializerJsonTest.cpp
)

target_link_libraries(
    test_loghero_lib
    ${GTEST_LIBRARIES}
    pthread
    loghero
)

add_test(
    NAME test_loghero_lib
    COMMAND test_loghero_lib
)
