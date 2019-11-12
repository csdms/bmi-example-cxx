include (CTest)

include_directories( ${CMAKE_SOURCE_DIR}/heat )

function(make_test test_name)
  add_test(NAME ${test_name} COMMAND ${test_name})
  add_executable(${test_name} ${test_name}.cxx)
  target_link_libraries(${test_name} bmiheatcxx)
endfunction(make_test)

make_test(test_irf)
make_test(test_print_var_names)
make_test(test_get_value)
make_test(test_set_value)
make_test(test_grid_info)
make_test(test_initialize_from_file)
make_test(test_reinitialize)
make_test(test_conflicting_instances)

file(
  COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.txt
  DESTINATION ${CMAKE_BINARY_DIR}/testing
)
