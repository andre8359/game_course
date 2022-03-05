cmake_minimum_required(VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/release/0.17/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
                ogg/1.3.5
                sfml/2.5.1
                nlohmann_json/3.10.5
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)


conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                     BUILD missing
                     REMOTE conancenter
                     SETTINGS ${settings}) 