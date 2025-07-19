# heatcxx

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${model_name}.pc.cmake
  ${CMAKE_BINARY_DIR}/heat/${model_name}.pc
)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${bmi_name}.pc.cmake
  ${CMAKE_BINARY_DIR}/heat/${bmi_name}.pc
)

if(WIN32)
  add_library(${model_name} heat.cxx)
  add_library(${bmi_name} bmi_heat.cxx heat.cxx)
else()
  add_library(${model_name} SHARED heat.cxx)
  add_library(${bmi_name} SHARED bmi_heat.cxx heat.cxx)
endif()
target_include_directories(${bmi_name} PUBLIC ${BMICXX_INCLUDE_DIRS})

add_executable(run_${bmi_name} bmi_main.cxx)
target_link_libraries(run_${bmi_name} ${bmi_name})

install(
  TARGETS run_${bmi_name}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
  TARGETS ${model_name} ${bmi_name}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(
  FILES bmi_heat.hxx heat.hxx
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${model_name}.pc
    ${CMAKE_CURRENT_BINARY_DIR}/${bmi_name}.pc
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
