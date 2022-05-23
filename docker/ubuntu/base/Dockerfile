FROM ubuntu:20.04

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
&& apt update -y \
&& DEBIAN_FRONTEND=noninteractive apt install -y -f \
    g++ \
    cmake \
    python3 \
    python3-pip \
    wget \
    net-tools \
    curl \
    dstat \
    make \
    git \
&& pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
