import subprocess
import sys
from pathlib import Path

file_path = Path(sys.argv[1])
print(file_path)

for file in file_path.glob("*.dwg"):
    print("processing {}".format(file))
    
    command = './e2dx-converter -i {} -o /mnt/2_modules/converted/2d/{}.e2dx'.format(file, file.stem)
    print(command)
    subprocess.run(command.split())
    subprocess.run(['mv', file, '/mnt/2_modules/converted/2d/source'])
