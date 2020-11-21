# simple check for a git repo
if(EXISTS "${GIT_DIR}/.git")
	find_package(Git)

    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%ci
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_TIME
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

else(EXISTS "${GIT_DIR}/.git")
    set(GIT_BRANCH "")
    set(GIT_COMMIT_HASH "")
    set(GIT_VERSION_NUMBER "")
    set(BUILD_TYPE "")

endif(EXISTS "${GIT_DIR}/.git")

string(TIMESTAMP CURRENTTIME "%Y-%m-%d %H:%M:%S")

MESSAGE(STATUS "---" ${GIT_DIR})

configure_file(
    ${CMAKE_SOURCE_DIR}/productVersion.h.in
    # 目的地址最好别选build路径的一部分, 会有权限错误
	${CMAKE_SOURCE_DIR}/header/productVersion.h
)

# message(STATUS "Git current branch: ${GIT_BRANCH}")
# message(STATUS "Git commit hash: ${GIT_COMMIT_HASH}")
# message(STATUS "Git commit time: ${GIT_COMMIT_TIME}")
# message(STATUS "CURRENT DIR NAME: ${CMAKE_SOURCE_DIR}/productVersion.h.in ${CMAKE_BINARY_DIR}/header/productVersion.h")
# message(STATUS "time: ${CURRENTTIME}")