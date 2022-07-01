import subprocess
import os
from pathlib import Path

HOME = Path.home()
CONFIG_DIR = HOME.joinpath('.config')


home_files = [
    HOME.joinpath('.zshrc'),
    HOME.joinpath('.zshenv'),
    HOME.joinpath('.dwm'),
    HOME.joinpath('.Xresources'),
    HOME.joinpath('.xinitrc'),
    HOME.joinpath('.xprofile'),
    HOME.joinpath('.fonts.conf'),
]

config_files = [    CONFIG_DIR.joinpath('zellij'),
    CONFIG_DIR.joinpath('alacritty'),
    CONFIG_DIR.joinpath('dunst'),
    CONFIG_DIR.joinpath('rofi'),
    CONFIG_DIR.joinpath('polybar'),
    CONFIG_DIR.joinpath('bat')
]
print('----------------------------------------------------')
print('files:')
files_str = '\n'.join(str(f) for f in [config_files, home_files])
print(files_str)


# copy the config files to current directory
print('----------------------------------------------------')
print('copying files to current directory')
for f in home_files:
    print('copying:', f)
    subprocess.run(['cp', f, '.', '-r'])

for f in config_files:
    print('copying:', f)
    subprocess.run(['cp', f, './.config/', '-r'])