# bmi-example-cxx

cmake_minimum_required(VERSION 3.16)
project(bmi-example-cxx
    VERSION 2.1.2
    LANGUAGES CXX
)

include(GNUInstallDirs)

set(model_name heatcxx)
set(bmi_name bmi${model_name})

if(LINUX)
    set(_linker_flags "-Wl,-z,now")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${_linker_flags}")
endif(LINUX)
# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(BMICXX REQUIRED IMPORTED_TARGET bmicxx)
list(APPEND CMAKE_MESSAGE_INDENT "  ")
message(STATUS "Include directory: ${BMICXX_INCLUDE_DIRS}")
list(POP_BACK CMAKE_MESSAGE_INDENT)

add_subdirectory(heat)
add_subdirectory(testing)

include (CTest)
