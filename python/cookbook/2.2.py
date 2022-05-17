filename = 'spam.txt'
print(filename.endswith('.txt'))
print(filename.startswith('spam.'))

import os
filenames = os.listdir('.')
print([name for name in filenames if name.endswith(('.py', '.PY'))])


from urllib.request import urlopen

def read_data(name):
    if name.startswith(('http:', 'https:', 'ftp:')):
        return urlopen(name).read()
    else:
        with open(name) as f:
            return f.read()

print(read_data('https://www.baidu.com'))
print(read_data('./3.4.2.py'))