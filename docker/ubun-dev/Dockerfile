FROM ubuntu:18.04 as ubuntu_base_env

#aliyun apt src for ubuntu18.
#RUN echo 'deb http://mirrors.aliyun.com/ubuntu/ focal main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security multiverse\n' > /etc/apt/sources.list \
RUN echo 'deb http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse' > /etc/apt/sources.list \
    && apt update && apt upgrade -y

RUN DEBIAN_FRONTEND=noninteractive apt install -y -f \
    build-essential \
    g++ \
    cmake \
    python3 \
    wget \
    net-tools \
    curl \
    git \
    gdb \
    dstat \
    make \
    iputils-ping

RUN apt install -y \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libiberty-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    pkg-config \
    libunwind-dev \
    libpcre3 libpcre3-dev


FROM ubuntu_base_env AS ubuntu_build_env
# replace github.com with mirro [hub.fastgit.org] to speed up.
#gtest
RUN mkdir -p /root/libs/ 
RUN cd /root/libs/ && \
    wget https://hub.fastgit.org/google/googletest/archive/release-1.8.0.tar.gz && \
    tar zxf release-1.8.0.tar.gz && \
    rm -f release-1.8.0.tar.gz && \
    cd googletest-release-1.8.0 && \
    cmake . && \
    make && \
    make install

#fmt
RUN cd /root/libs/ && \
    git clone https://hub.fastgit.org/fmtlib/fmt.git && cd fmt && \
    mkdir _build && cd _build && \
    cmake .. && \
    make -j$(nproc) && \
    make install

#not remove cache
#RUN rm -rf /root/libs
#RUN rm -rf /var/lib/apt/lists/*
