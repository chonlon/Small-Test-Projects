cmake_minimum_required(VERSION 3.0.2)
project(folly)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(asio)


set(
	LinkLibs
	Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util
	ZLIB::ZLIB
)

add_executable(future1 future1.cpp)
target_link_libraries(future1 PRIVATE ${LinkLibs})

if (${asio_FOUND}) 
	add_executable(async_server async_server.cpp)
	target_link_libraries(async_server PRIVATE ${LinkLibs} asio asio::asio)
else(${asio_FOUND})
	MESSAGE("asio not found")
endif(${asio_FOUND}) 
