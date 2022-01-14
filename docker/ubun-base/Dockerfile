FROM ubuntu:20.04 as ubuntu_base_env

RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
&& apt update -y \
&& DEBIAN_FRONTEND=noninteractive apt install -y -f \
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
    iputils-ping \
    zsh

COPY ./install_zsh.sh /root/install_zsh.sh

RUN sh /root/install_zsh.sh && echo 'source /usr/share/zsh-autosuggestions/zsh-autosuggestions.zsh && source /usr/share/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh' >> /root/.zshrc

CMD ["zsh"]
