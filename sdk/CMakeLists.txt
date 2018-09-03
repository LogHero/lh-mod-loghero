set(LH_SDK_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LH_SDK_CLIENT_ID "\"C++ SDK loghero/sdk@0.0.1\"")
add_definitions(-DLH_SDK_CLIENT_ID=${LH_SDK_CLIENT_ID})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})


set(BOOST_LOG_COMPONENT "")
set(LOG_SOURCE_FILES "")
if(LH_ENABLE_LOGGING)
  set(BOOST_LOG_COMPONENT log)
  set(LOG_SOURCE_FILES LoggingPolicyBoost.h LoggingPolicyBoost.cpp)
endif(LH_ENABLE_LOGGING)


find_package(JsonCpp REQUIRED)
find_package(Boost COMPONENTS ${BOOST_LOG_COMPONENT} system iostreams REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(Loki REQUIRED)


include_directories(
    .
    ${JsonCpp_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    ${Loki_INCLUDE_DIR}
)

link_directories(
    ${JsonCpp_LIB_DIRS}
)

add_library(loghero_sdk STATIC
    GlobalDefines.h
    LogHeroSettings.h
    LogHeroSingleton.h
    LogHeroSingleton.cpp
    LogHeroSessionInterface.h
    LogHeroSession.h
    LogEvent.h
    LogEvent.cpp
    LogEventSerializerJson.h
    LogEventSerializerJson.cpp
    APIAccess.h
    Zlib.h
    Zlib.cpp
    HttpRequestInterface.h
    HttpRequestCurl.h
    HttpRequestCurl.cpp
    LogBuffer.h
    LogContainerPolicyInMemory.h
    LockingPolicyLockGuard.h
    TimerPolicyCTime.h
    SubmitPolicySync.h
    SubmitPolicyAsync.h
    Logging.h
    LoggingPolicyDisabled.h
    ${LOG_SOURCE_FILES}
)

add_library(loghero SHARED
    LibLogHero.h
    LibLogHero.cpp
)

target_link_libraries(
    loghero
    loghero_sdk
    ${JsonCpp_LIBRARIES}
    ${Boost_LIBRARIES}
    ${ZLIB_LIBRARIES}
    ${CURL_LIBRARIES}
    ${OPENSSL_LIBRARIES}
    dl
)

install(
    TARGETS loghero
    DESTINATION lib
)

add_subdirectory(3rd)
add_subdirectory(test)
