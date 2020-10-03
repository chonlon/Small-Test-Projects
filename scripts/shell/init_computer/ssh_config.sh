apt-get install openssh-server
#config ssh
cd ~ && mkdir .ssh && chmod 700 .ssh && cd .ssh/ && touch authorized_keys && chmod 600 authorized_keys 
echo -e "ssh config succeed.\033[31m REMEMBER TO ADD KEY TO authorized_keys \033[0m"
