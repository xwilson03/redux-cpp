find_package(Qt6 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

add_executable(qt_app
    qt_app.cpp
)
target_link_libraries(qt_app
    Qt6::Widgets
    example_store
)

install(
    TARGETS qt_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
