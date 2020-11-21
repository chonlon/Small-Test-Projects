cmake_minimum_required(VERSION 3.0.2)
project(versionTest)
include(version.cmake)



add_executable(main main.cpp)
target_include_directories(main PRIVATE ./header)

#采用这种方式强制使cmake在每次build的时候重新执行version.cmake..
#所以有个负面影响: 包含了这个头文件的编译单元build时需要重新编译..
#如果只需要GIT信息, 不需要每次都输出build time, 可以参考: https://stackoverflow.com/a/50104093/7059225 做到只有git信息更新时重新生成信息
# 或者还有一个原始一点的办法: 每次手动重新配置cmake(比如执行cmake ..), 不过这样容易忘记导致错误.
add_custom_target(
	versionnumber ALL
)

add_custom_command(
	TARGET versionnumber
	PRE_BUILD
	# -DGIT_DIR 一般等于${CMAKE_SOURCE_DIR}就可以, 这里是因为我这里不在项目根目录下面
	COMMAND ${CMAKE_COMMAND} -DGIT_DIR="${CMAKE_SOURCE_DIR}/../../../.." -P ${CMAKE_SOURCE_DIR}/version.cmake
	BYPRODUCTS ${CMAKE_BINARY_DIR}/header/productVersion.h
	DEPENDS "main"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "check/update version number"
	)

add_dependencies(main versionnumber)
