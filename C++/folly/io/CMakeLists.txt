cmake_minimum_required(VERSION 3.0.2)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

set(
	LinkLibs
	Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util
	ZLIB::ZLIB
)

add_executable(iobuf iobuf.cpp)
target_link_libraries(iobuf PRIVATE ${LinkLibs})