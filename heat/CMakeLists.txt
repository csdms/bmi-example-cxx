cmake_minimum_required(VERSION 2.6)

project (heat)

set (HEAT_VERSION 0.1)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/heatcxx.pc.cmake
                ${CMAKE_CURRENT_SOURCE_DIR}/heatcxx.pc)

set (BUILD_SHARED_LIBS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(bmi_heat_lib_SRCS bmi_heat.cxx heat.cxx)
add_library(bmi_heatcxx ${bmi_heat_lib_SRCS} )


########### Install files ###############

install(FILES bmi_heat.hxx DESTINATION include/heat COMPONENT heat)
install(FILES heat.hxx DESTINATION include/heat COMPONENT heat)
install(FILES heatcxx.pc DESTINATION lib/pkgconfig)
install(TARGETS bmi_heatcxx DESTINATION lib COMPONENT heat)
