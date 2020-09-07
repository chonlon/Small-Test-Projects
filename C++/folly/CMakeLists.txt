cmake_minimum_required(VERSION 3.0.2)
project(folly)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(future)
add_subdirectory(io)

set(
	LinkLibs
	Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util
	ZLIB::ZLIB
)

OPTION(UsingJemalloc "if using jemalloc" on)
if(UsingJemalloc)
	message(STATUS "jemalloc enabled!")
	set(
		LinkLibs
		${LinkLibs}
		jemalloc
	)
endif(UsingJemalloc)

add_executable(fbvector fbvector.cpp)
target_link_libraries(fbvector ${LinkLibs})

add_executable(fbjson ${CMAKE_CURRENT_LIST_DIR}/json/json1.cpp)
target_link_libraries(fbjson ${LinkLibs})