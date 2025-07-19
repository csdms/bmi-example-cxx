# bmi-example-cxx

cmake_minimum_required(VERSION 3.16)
project(bmi-example-cxx
    VERSION 2.1.2
    LANGUAGES CXX
)

include(GNUInstallDirs)

set(model_name heatcxx)
set(bmi_name bmi${model_name})

find_package(PkgConfig REQUIRED)
pkg_check_modules(BMICXX REQUIRED IMPORTED_TARGET bmicxx)
list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(STATUS "Include directory: ${BMICXX_INCLUDE_DIRS}")
list(POP_BACK CMAKE_MESSAGE_INDENT)

add_subdirectory(heat)
add_subdirectory(testing)

include (CTest)
