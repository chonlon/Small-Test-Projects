project(stds)
cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 17)
include(../../cmake/AddSingleExeFile.cmake)

AddSingleExeFile(
	STD_LIB
	"regex/regex.cpp"
	"any/any.cpp"
)

foreach(FILESPATH ${STD_LIB_FILES})
	get_filename_component(FILE_NAME ${FILESPATH} NAME_WE)
	add_executable(${FILE_NAME} ${FILESPATH})
endforeach()