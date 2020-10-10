cmake_minimum_required(VERSION 3.0.2)
project(folly)

find_package(folly CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

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


add_executable(fbvector ${CMAKE_CURRENT_LIST_DIR}/vector/fbvector.cpp)
target_link_libraries(fbvector ${FbvectorLinkLibs})

add_executable(fbvector_custom_alloctor ${CMAKE_CURRENT_LIST_DIR}/vector/fbvector_custom_alloctor.cpp)
target_link_libraries(fbvector_custom_alloctor ${FbvectorLinkLibs})

add_executable(fbjson ${CMAKE_CURRENT_LIST_DIR}/json/json1.cpp)
target_link_libraries(fbjson ${LinkLibs})

add_executable(future1 ${CMAKE_CURRENT_LIST_DIR}/future/future1.cpp)
target_link_libraries(future1 PRIVATE ${LinkLibs})

add_executable(future2 ${CMAKE_CURRENT_LIST_DIR}/future/future2.cpp)
target_link_libraries(future2 PRIVATE ${LinkLibs})

add_executable(iobuf ${CMAKE_CURRENT_LIST_DIR}/io/iobuf.cpp)
target_link_libraries(iobuf PRIVATE ${LinkLibs})

add_executable(trait1 trait1.cpp)
target_link_libraries(trait1 PRIVATE ${LinkLibs})

add_executable(iterator ./container/iterator.cpp)
target_link_libraries(iterator PRIVATE ${LinkLibs})