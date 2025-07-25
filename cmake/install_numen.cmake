option(INSTALL_SYSTEM_WIDE "Install system-wide" ON)

if(INSTALL_SYSTEM_WIDE)
    include(GNUInstallDirs)

    # install library targets
    install(TARGETS numen_interface numen_shared numen_static
        EXPORT numen-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    # install headers
    install(DIRECTORY numen/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/numen)

    # install config files
    install(EXPORT numen-targets 
        FILE numen-config.cmake 
        NAMESPACE numen:: 
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/numen
    )

    # generate pkg-config file
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/numen.pc.in
        ${CMAKE_CURRENT_BINARY_DIR}/numen.pc
        @ONLY
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/numen.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    )
endif()
