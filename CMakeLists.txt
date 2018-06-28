cmake_minimum_required(VERSION 2.8.9)
project (lh-mod-loghero)

set(APXS_OPTIONS -i -a)
set(APXS_SUDO sudo)

add_custom_target(
    mod_loghero
    COMMAND ${APXS_SUDO} apxs ${APXS_OPTIONS} -c ${CMAKE_CURRENT_SOURCE_DIR}/mod_loghero.c
    SOURCES mod_loghero
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(sdk)
