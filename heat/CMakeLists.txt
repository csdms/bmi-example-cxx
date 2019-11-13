cmake_minimum_required(VERSION 3.0)

set (HEAT_VERSION 0.2)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/heatcxx.pc.cmake
                ${CMAKE_BINARY_DIR}/heatcxx.pc)

set(bmi_heat_lib_SRCS bmi_heat.cxx heat.cxx)
if(WIN32)
  add_library(bmiheatcxx ${bmi_heat_lib_SRCS})
else()
  add_library(bmiheatcxx SHARED ${bmi_heat_lib_SRCS})
endif()

add_executable(run_bmiheatcxx bmi_main.cxx bmi_heat.cxx heat.cxx)

install(
  TARGETS run_bmiheatcxx
  RUNTIME DESTINATION bin
)
install(
  TARGETS bmiheatcxx
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)
install(
  FILES bmi_heat.hxx heat.hxx
  DESTINATION include
)
install(
  FILES ${CMAKE_BINARY_DIR}/heatcxx.pc
  DESTINATION lib/pkgconfig
)
