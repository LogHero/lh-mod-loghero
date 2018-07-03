
add_library(loghero SHARED
    LibLogHero.h
    LibLogHero.cpp
    GlobalDefines.h
    LogEvent.h
)

install(
    TARGETS loghero
    DESTINATION lib
)

add_subdirectory(test)
