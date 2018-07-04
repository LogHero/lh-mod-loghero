if(IS_DIRECTORY ${CONAN_JSONCPP_ROOT})
    set(JsonCpp_FOUND TRUE)
    set(JsonCpp_INCLUDE_DIRS ${CONAN_INCLUDE_DIRS_JSONCPP})
    set(JsonCpp_LIB_DIRS ${CONAN_LIB_DIRS_JSONCPP})
    set(JsonCpp_LIBRARIES ${CONAN_LIBS_JSONCPP})
else(IS_DIRECTORY ${CONAN_JSONCPP_ROOT})
    message(STATUS "JsonCpp NOT found")
    set(JsonCpp_FOUND FALSE)
endif(IS_DIRECTORY ${CONAN_JSONCPP_ROOT})