FROM ubuntu:20.04

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
&& apt update && apt upgrade -y \
&& DEBIAN_FRONTEND=noninteractive \
 apt install cmake g++ net-tools vim python3 python3-pip  curl wget gdb -y \
&& pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
