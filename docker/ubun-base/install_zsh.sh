apt install zsh zsh-syntax-highlighting zsh-autosuggestions -y
#oh my zsh
#may with proxy: export https_proxy="http:\\ip:port"
# sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
sh -c "$(wget -O- https://gitee.com/shmhlsy/oh-my-zsh-install.sh/raw/master/install.sh)"

apt install -y 
sed -i 's/^plugins=(.*/plugins=(autojump zsh-syntax-highlighting zsh-autosuggestions)/' /root/.zshrc
