import os.path
import subprocess

if not os.path.isfile('./build/test1'):
    print('./build/test1 was not exists, trying to build it..., but notion: you may change build command as you needed')
    subprocess.call(['mkdir', 'build'])
    #vcpkg installed toolchain file dir
    subprocess.check_call(['cmake', '..', '-DCMAKE_TOOLCHAIN_FILE=/home/lon/2_lib/vcpkg/scripts/buildsystems/vcpkg.cmake'], cwd='./build')
    subprocess.call(['cmake', '--build', './build'])

print('*'*20, ' helpshort ','*'*20)
subprocess.call(['./build/test1', '--helpshort'])
print('*'*20, ' run ', '*'*20)
subprocess.call(['./build/test1', '-big_menu=false','-languages=chinese'])
