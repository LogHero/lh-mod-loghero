cmake_minimum_required(VERSION 3.5)
project (lh-mod-loghero)

set(LH_MOD_CLIENT_ID "\"Apache Module loghero/httpd@0.0.1\"")
add_definitions(-DLH_MOD_CLIENT_ID=${LH_MOD_CLIENT_ID})
set(CMAKE_CXX_FLAGS "-g -Wall -Wno-unused-local-typedefs -fPIC")

if(LH_ENABLE_LOGGING)
  add_definitions(-DLH_ENABLE_LOGGING=1)
  set(APX_DEFINITIONS "-D LH_ENABLE_LOGGING=1")
endif(LH_LOG_LEVEL)

include(conanbuildinfo.cmake)
conan_set_find_paths()
enable_testing()

set(APXS_OPTIONS -i -a)
set(APXS_SUDO sudo)

add_custom_target(mod_loghero
    COMMAND ${APXS_SUDO} apxs ${APXS_OPTIONS} -I ${CMAKE_CURRENT_SOURCE_DIR}/sdk -L ${CMAKE_INSTALL_PREFIX}/lib ${APX_DEFINITIONS} -l loghero -c ${CMAKE_CURRENT_SOURCE_DIR}/mod_loghero.c
    SOURCES mod_loghero
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_subdirectory(sdk)
