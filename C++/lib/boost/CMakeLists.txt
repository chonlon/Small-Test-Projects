cmake_minimum_required(VERSION 3.0.2)
project(boost)

include(../../cmake/AddSingleExeFile.cmake)

add_subdirectory(algorithm)
add_subdirectory(beast)
add_subdirectory(serialization)

AddFilesToParent(
	BOOST_OTHER
	"assignment/assignment.cpp"
)
find_package(Boost 1.67 COMPONENTS serialization REQUIRED)

ADDEXEFROMFILESWITHINCLUDE("${BOOST_INCLUDE_DIRS}" "" ${ALGORITHM_FILES})
ADDEXEFROMFILESWITHINCLUDE("${BOOST_INCLUDE_DIRS}" "pthread" ${BEAST_FILES})
ADDEXEFROMFILESWITHINCLUDE("${BOOST_INCLUDE_DIRS}" "" ${BOOST_OTHER_FILES})
ADDEXEFROMFILESWITHINCLUDE("${BOOST_INCLUDE_DIRS}" "${Boost_LIBRARIES}" ${Serialize_FILES})


# foreach(FILESPATH ${ALGORITHM_FILES})
# 	get_filename_component(FILE_NAME ${FILESPATH} NAME_WE)
# 	add_executable(${FILE_NAME} ${FILESPATH})
# 	target_include_directories(${FILE_NAME}  PRIVATE ${BOOST_INCLUDE_DIRS})
# endforeach()

# foreach(FILESPATH ${BEAST_FILES})
# 	get_filename_component(FILE_NAME ${FILESPATH} NAME_WE)
# 	add_executable(${FILE_NAME} ${FILESPATH})
# 	target_include_directories(${FILE_NAME}  PRIVATE ${BOOST_INCLUDE_DIRS})
# endforeach()

# foreach(FILESPATH ${BOOST_OTHER_FILES})
# 	get_filename_component(FILE_NAME ${FILESPATH} NAME_WE)
# 	add_executable(${FILE_NAME} ${FILESPATH})
# 	target_include_directories(${FILE_NAME}  PRIVATE ${BOOST_INCLUDE_DIRS})
# endforeach()

# foreach(FILESPATH ${Serialize_FILES})
# 	get_filename_component(FILE_NAME ${FILESPATH} NAME_WE)
# 	add_executable(${FILE_NAME} ${FILESPATH})
# 	target_include_directories(${FILE_NAME}  PRIVATE ${BOOST_INCLUDE_DIRS})
# 	target_link_libraries(${FILE_NAME} PRIVATE ${Boost_LIBRARIES})
# endforeach()
