cmake_minimum_required(VERSION 3.20)
project(mine_occt_demo)

set(CMAKE_CXX_STANDARD 17)



add_executable(mine_occt_demo main.cpp StepReader.hpp)
target_include_directories(mine_occt_demo
        PRIVATE
        /usr/local/include/opencascade
        /mnt/data/1_lib/vcpkg/installed/x64-linux/include/argparse
        )
target_link_libraries(mine_occt_demo
        PRIVATE
        TKernel
        TKIGES
        TKMath
        TKBRep
        TKXCAF
        TKLCAF
        TKXSBase
        TKXDEIGES
        TKXDESTEP
        TKTopAlgo
        TKMesh
        TKG3d
        TKV3d
        )