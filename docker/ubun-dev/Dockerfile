FROM ubuntu:20.04 as builder

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
&& apt update && apt upgrade -y \
&& DEBIAN_FRONTEND=noninteractive apt install g++ cmake git wget unzip rapidjson-dev ninja-build gdb  python python3-pip -y
