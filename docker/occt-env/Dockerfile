FROM ubuntu:20.04

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
&& apt update && apt upgrade -y \
&& DEBIAN_FRONTEND=noninteractive \
  apt install cmake doxygen ninja-build g++ tcllib tklib tcl-dev tk-dev rapidjson-dev libboost-all-dev libeigen3-dev libfreeimage-dev libfreetype-dev libgl1-mesa-dev libssl-dev libxmu-dev libxi-dev libx11-dev -y \


