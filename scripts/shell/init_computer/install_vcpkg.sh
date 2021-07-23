#vcpkg
mkdir ~/2_lib
cd ~/2_lib
git clone https://github.com/microsoft/vcpkg.git 
cd ~/2_lib/vcpkg && sh ./bootstrap-vcpkg.sh
./vcpkg install boost:x64-linux
./vcpkg install range-v3:x64-linux
./vcpkg install fmt:x64-linux