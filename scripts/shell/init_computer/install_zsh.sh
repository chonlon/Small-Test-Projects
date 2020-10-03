#zsh
apt install zsh && chsh -s /bin/zsh
#oh my zsh
#may with proxy: export https_proxy="http:\\ip:port"
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
    # options
    # cd ~/.oh-my-zsh/plugins
    # mkdir incr && cd incr
    # wget http://mimosa-pudica.net/src/incr-0.2.zsh
#autosuggestions
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
#highlight
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git $ZSH_CUSTOM/plugins/zsh-syntax-highlighting
echo "source ${(q-)PWD}/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> ${ZDOTDIR:-$HOME}/.zshrc
echo -e "alias cdco=cd /mnt/1_code/\nalias py=python3"  >> ${ZDOTDIR:-$HOME}/.zshrc
source ~/.zshrc