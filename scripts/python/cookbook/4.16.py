import sys

def reader():
    f = open('/etc/passwd')
    for chunk in iter(lambda: f.read(10), ''):
        n = sys.stdout.write(chunk)

reader()
