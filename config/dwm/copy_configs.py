"""
Copy All Dwm config files to your home dir, Use it Carefully.
"""
from pathlib import Path
import subprocess


config_files = [
    Path(".config"),
    Path(".doom.d"),
    Path(".dmenu"),
    Path(".local"),
    Path(".Xresources"),
    Path(".xinitrc"),
    Path(".xprofile"),
    Path(".zshrc"),
    Path('.zshenv'),
    Path(".nord"),
    Path(".nord_dir"),
    Path(".one_dir"),
    Path(".onehalflight"),
    Path(".onehalflight"),
]

print("----------------------------------------------------")
print("config files: {}".format('\n'.join(str(x) for x in config_files)))

for config_file in config_files:
    print(f"Copying {config_file}")
    subprocess.run(["cp", "-r", str(config_file), str(Path.home())])

print("----------------------------------------------------")
