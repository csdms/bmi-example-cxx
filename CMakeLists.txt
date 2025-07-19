# bmi-example-cxx

cmake_minimum_required(VERSION 3.12)
project(bmi-example-cxx
    VERSION 2.1.2
    LANGUAGES CXX
)

include(GNUInstallDirs)

set(model_name heatcxx)
set(bmi_name bmi${model_name})

find_package(PkgConfig REQUIRED)
pkg_check_modules(BMICXX REQUIRED IMPORTED_TARGET bmicxx)
message("--   bmicxx include dir - ${BMICXX_INCLUDE_DIRS}")

add_subdirectory(heat)
add_subdirectory(testing)

include (CTest)
