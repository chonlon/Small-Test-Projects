FROM ubuntu:20.04 as builder

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
&& apt update && apt upgrade -y \
&& DEBIAN_FRONTEND=noninteractive apt install g++ cmake git wget unzip rapidjson-dev ninja-build gdb -y

WORKDIR /root

RUN wget https://github.com/google/draco/archive/refs/tags/1.4.3.zip && \
unzip 1.4.3.zip && \
cd draco-1.4.3/ && \
mkdir build && cd build && \
cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE && ninja && ninja install && \
cd && \
wget https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip && \
unzip fmt-8.1.1.zip  && \
cd fmt-8.1.1 && \
mkdir build && cd build && \
cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE && ninja && ninja install && \
cd && \
wget https://github.com/p-ranav/argparse/archive/refs/tags/v2.2.zip && \
unzip v2.2.zip && \
cd argparse-2.2/ && \
mkdir build && cd build && \
cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE && ninja && ninja install && \
cd && rm -rf *
