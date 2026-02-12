add_library(example_store)
target_sources(example_store
  PUBLIC FILE_SET example_store TYPE CXX_MODULES FILES
    example_store.cppm
)
target_link_libraries(example_store
    redux
)
