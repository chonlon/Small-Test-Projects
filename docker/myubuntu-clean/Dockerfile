FROM ubuntu
RUN echo 'deb http://mirrors.aliyun.com/ubuntu/ focal main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security multiverse\n' > /etc/apt/sources.list \
    && buildDeps='python3 python3-pip build-essential' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && rm -rf /var/lib/apt/lists/* \
#    && apt-get purge -y --auto-remove $buildDeps
