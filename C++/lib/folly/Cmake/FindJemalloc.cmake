find_path(LIBJEMALLOC_INCLUDE_DIR jemalloc/jemalloc.h)
mark_as_advanced(LIBJEMALLOC_INCLUDE_DIR)

find_library(LIBJEMALLOC_LIBRARY NAMES jemalloc)
mark_as_advanced(LIBJEMALLOC_LIBRARY)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    LIBJEMALLOC
    DEFAULT_MSG
    LIBJEMALLOC_LIBRARY LIBJEMALLOC_INCLUDE_DIR)

if(LIBJEMALLOC_FOUND)
    set(LIBJEMALLOC_LIBRARYS ${LIBJEMALLOC_LIBRARY})
    set(LIBJEMALLOC_INCLUDE_DIRS ${LIBJEMALLOC_INCLUDE_DIR})
    message(STATUS "Found {jemalloc}: ${LIBJEMALLOC_LIBRARY}")
    add_library(jemalloc UNKNOWN IMPORTED)
    set_target_properties(
      jemalloc PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${LIBJEMALLOC_INCLUDE_DIR}"
    )
    set_target_properties(
      jemalloc PROPERTIES
      IMPORTED_LINK_INTERFACE_LANGUAGES "C"
      IMPORTED_LOCATION "${LIBJEMALLOC_LIBRARY}"
    )
endif()
