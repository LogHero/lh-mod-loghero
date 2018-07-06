set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(JsonCpp REQUIRED)
find_package(Boost COMPONENTS system iostreams REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)


include_directories(
    .
    ${JsonCpp_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

link_directories(
    ${JsonCpp_LIB_DIRS}
)

add_library(loghero SHARED
    LibLogHero.h
    LibLogHero.cpp
    GlobalDefines.h
    LogEvent.h
    LogEvent.cpp
    LogEventSerializerInterface.h
    LogEventSerializerJson.h
    LogEventSerializerJson.cpp
    APIAccessInterface.h
    APIAccess.h
    APIAccess.cpp
    Zlib.h
    Zlib.cpp
    HttpRequestInterface.h
    HttpRequestCurl.h
    HttpRequestCurl.cpp
)

target_link_libraries(
    loghero
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

add_subdirectory(test)
