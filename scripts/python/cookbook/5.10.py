import os
import mmap

def memory_map(filename, access = mmap.ACCESS_WRITE):
    size = os.path.getsize(filename)
    fd = os.open(filename, os.O_RDONLY)
    return mmap.mmap(fd, size, access=access)

m = memory_map('/etc/os-release', mmap.ACCESS_READ)
print(len(m))
print(m[0:100])