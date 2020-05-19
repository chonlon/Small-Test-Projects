cmake_minimum_required(VERSION 3.0.2)
project(folly)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(future)

set(
	LinkLibs
	Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util
	ZLIB::ZLIB
)

add_executable(fbvector fbvector.cpp)
target_link_libraries(fbvector PRIVATE ${LinkLibs})