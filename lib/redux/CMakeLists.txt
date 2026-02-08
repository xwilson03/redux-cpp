add_library(redux)
target_sources(redux
  PRIVATE
  PUBLIC FILE_SET redux TYPE CXX_MODULES FILES
    redux.cppm
    store.cppm
)
