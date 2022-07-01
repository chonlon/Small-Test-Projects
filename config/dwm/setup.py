import subprocess


dwm_apps = "dex xob polybar-dwm-module rofi dmenu dunst i3lock-color xautolock xsettingsd conky picom-ibhagwan-git"

user_apps = "clash-for-windows-bin copyq utools google-chrome fzf btop htop rg alacritty zellij kitty neovim zsh fish feh"

lang_apps = "clang gcc python python-pip node gdb cmake rustup jetbrains-toolbox "

fonts = "nerd-fonts-ibm-plex-mono nerd-fonts-fira-code nerd-fonts-jetbrains-mono ttf-sarasa-gothic nerd-fonts-dejavu-sans-mono"

print("=============== Installing Apps ===============")


def install_app(apps, name):
    print(f"--------- {name} -------------")
    print(apps, "\n", "\n")
    pkg_install_cmd = "yay -S "
    subprocess.run(pkg_install_cmd + apps, shell=True)


install_app(fonts, "fonts")
install_app(dwm_apps, "dwm apps")
install_app(user_apps, "user apps")
install_app(lang_apps, "lang apps")

print("=============== setup env ==================")
