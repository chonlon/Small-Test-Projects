FROM ubuntu
RUN sed -i 's/archive.ubuntu.com/mirrors.ustc.edu.cn/g' /etc/apt/sources.list \
    && buildDeps='python3 python3-pip build-essential wget gdb ninja' \
    && Apps="dstat htop git"
    && apt-get update \
    && apt-get install -y $buildDeps \
#zshs

#RUN git clone https://github.com/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh \
RUN git clone https://hub.fastgit.org/robbyrussell/oh-my-zsh.git ~/.oh-my-zsh \
    && cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc \
    && chsh -s /bin/zsh \
    && git clone https://hub.fastgit.org/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
#end zshs
