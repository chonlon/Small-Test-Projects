FROM ubuntu
RUN echo 'deb http://mirrors.aliyun.com/ubuntu/ focal main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-updates multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security universe\ndeb http://mirrors.aliyun.com/ubuntu/ focal-security multiverse\n' > /etc/apt/sources.list \
    && buildDeps='python3 python3-pip build-essential wget' \
    && apt-get update \
    && apt-get install -y $buildDeps
#zshs
RUN apt-get install -y \
    zsh \
    git-core
RUN git clone https://github.com/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh \
    && cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc \
    && chsh -s /bin/zsh
#end zshs