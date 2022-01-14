FROM ubuntu:18.04 as ubuntu_base_env

#aliyun apt src for ubuntu18.
#RUN echo 'deb http://mirrors.aliyun.com/ubuntu/ focal main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security multiverse\n' > /etc/apt/sources.list \
RUN echo 'deb http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse\ndeb http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-security main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-updates main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-proposed main restricted universe multiverse\ndeb-src http://mirrors.163.com/ubuntu/ bionic-backports main restricted universe multiverse' > /etc/apt/sources.list \
    && apt update && apt upgrade -y

RUN DEBIAN_FRONTEND=noninteractive apt install -y -f \
    g++ \
    build-essential \
    cmake \
    python3 \
    wget \
    net-tools \
    curl \
    git \
    gdb \
    dstat \
    make \
    iputils-ping \
