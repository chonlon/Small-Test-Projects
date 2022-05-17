#读写压缩文件

# gzip compression
import bz2
import gzip

with gzip.open('somefile.gz', 'rt') as f:
    text = f.read()
# bz2 compression
with bz2.open('somefile.bz2', 'rt') as f:
    text = f.read()
