cmake_minimum_required(VERSION 3.0.2)
project(folly)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

include(../../cmake/AddSingleExeFile.cmake)

set(
	LinkLibs
	Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util
	ZLIB::ZLIB
)

set(FbvectorLinkLibs
	${LinkLibs}
)

OPTION(UsingJemalloc "if using jemalloc" off)
if(UsingJemalloc)
	message(STATUS "jemalloc enabled!")
	set(
		FbvectorLinkLibs
		${FbvectorLinkLibs}
		jemalloc
	)
endif(UsingJemalloc)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../header)

AddFilesTo(
	FOLLY_MAIN
	io/iobuf.cpp
	json/json1.cpp
	trait1.cpp
	container/iterator.cpp
	demangle.cpp
)

AddExeFromFiles("${LinkLibs}" ${FOLLY_MAIN_FILES})

add_subdirectory(future)
add_subdirectory(vector)
add_subdirectory(fbstring)
