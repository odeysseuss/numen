option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_STATIC_LIBS "Build static libraries" ON)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -pedantic -pipe -g -O2 -D_FORTIFY_SOURCE=2 -fstack-protector-all)
endif()

file(GLOB_RECURSE LIB_SOURCES "src/*.c")

# interface target for includes
add_library(numen_interface INTERFACE)
target_include_directories(numen_interface INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/numen>
    $<INSTALL_INTERFACE:include>
)

# shared library
if(BUILD_SHARED_LIBS)
    add_library(numen_shared SHARED ${LIB_SOURCES})
    target_link_libraries(numen_shared PUBLIC numen_interface m)
    set_target_properties(numen_shared PROPERTIES 
        OUTPUT_NAME "numen" 
        VERSION ${PROJECT_VERSION} 
        SOVERSION 1
    )
endif()

# static library
if(BUILD_STATIC_LIBS)
    add_library(numen_static STATIC ${LIB_SOURCES})
    target_link_libraries(numen_static PUBLIC numen_interface m)
    set_target_properties(numen_static PROPERTIES OUTPUT_NAME "numen")
    if(WIN32)
        set_target_properties(numen_static PROPERTIES OUTPUT_NAME "numen_s")
    endif()
endif()
