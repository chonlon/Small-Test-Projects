# !/usr/bin/env python

import subprocess
import sys
from pathlib import Path

# run cmake build
subprocess.run(['cmake', '--build', '.'])
file_path = Path(sys.argv[1])

if not (file_path.exists() or file_path.is_file()):
    print('file type error: file {}'.format(file_path))

file_name = file_path.stem

subprocess.run(['./converter', '-i', file_path,'--log', file_name + '.json'])
subprocess.run(['cp', './out.e3dx', '/home/lon/1_code/ever3d-kernel/'])

print('sucessful execute build')
