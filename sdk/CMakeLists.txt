set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(JsonCpp)

include_directories(
    .
    ${JsonCpp_INCLUDE_DIRS}
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
)

target_link_libraries(
    loghero
    ${JsonCpp_LIBRARIES}
)

install(
    TARGETS loghero
    DESTINATION lib
)

add_subdirectory(test)
