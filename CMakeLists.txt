cmake_minimum_required(VERSION 3.11)
project (lh-mod-loghero)

include(conanbuildinfo.cmake)
conan_set_find_paths()
enable_testing()

set(APXS_OPTIONS -i -a)
set(APXS_SUDO sudo)

add_custom_target(mod_loghero
    COMMAND ${APXS_SUDO} apxs ${APXS_OPTIONS} -I ${CMAKE_CURRENT_SOURCE_DIR}/sdk -L ${CMAKE_INSTALL_PREFIX}/lib -l loghero -c ${CMAKE_CURRENT_SOURCE_DIR}/mod_loghero.c
    SOURCES mod_loghero
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(sdk)
