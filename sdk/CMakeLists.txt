
add_library(loghero SHARED
    LibLogHero.h
    LibLogHero.cpp
)

install(
    TARGETS loghero
    DESTINATION lib
)

add_subdirectory(test)
