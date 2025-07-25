function(add_numen_test test_name)
    add_executable(${test_name} ${ARGN})
    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/nutest)
    target_link_libraries(${test_name} PRIVATE numen_interface)

    if(TARGET numen_shared)
        target_link_libraries(${test_name} PRIVATE numen_shared)
    else()
        target_link_libraries(${test_name} PRIVATE numen_static)
    endif()

    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()
