include_directories(
    .
)

add_library(loghero SHARED
    LibLogHero.h
    LibLogHero.cpp
    GlobalDefines.h
    LogEvent.h
    LogEvent.cpp
)

install(
    TARGETS loghero
    DESTINATION lib
)

add_subdirectory(test)
