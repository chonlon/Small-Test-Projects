#!/usr/bin/env bash

if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

UserName=${1:-lon}

echo "install on user: ${UserName}"


# echo "installing basic tools"
# DEBIAN_FRONTEND=noninteractive apt install -y -f \
#     build-essential \
#     g++ \
#     cmake \
#     python3 \
#     wget \
#     net-tools \
#     curl \
#     git \
#     gdb \
#     dstat \
#     make \
#     iputils-ping

# echo "installing dev env"
# apt install -y \
#     libboost-all-dev \
#     libevent-dev \
#     libdouble-conversion-dev \
#     libgoogle-glog-dev \
#     libgflags-dev \
#     libiberty-dev \
#     liblz4-dev \
#     liblzma-dev \
#     libsnappy-dev \
#     zlib1g-dev \
#     binutils-dev \
#     libjemalloc-dev \
#     libssl-dev \
#     pkg-config \
#     libunwind-dev \
#     libpcre3 libpcre3-dev


echo "switch to ${UserName}"
su "${UserName}"
# mkdir test1
cd ~
mkdir 2_libsss
cd 2_libsss
echo echo "clone and build libs to $pwd"
su root
