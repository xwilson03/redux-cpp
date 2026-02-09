
add_library(example_store)
target_sources(example_store
  PRIVATE
  PUBLIC FILE_SET example_store TYPE CXX_MODULES FILES
    example_store.cppm
)
target_link_libraries(example_store
    redux
)


add_executable(example_app
    example_app.cpp
)
target_link_libraries(example_app
    example_store
)

install(
    TARGETS example_app
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
