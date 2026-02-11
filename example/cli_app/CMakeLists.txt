add_executable(cli_app
    cli_app.cpp
)
target_link_libraries(cli_app
    example_store
)

install(
    TARGETS cli_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
