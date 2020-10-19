from fnmatch import fnmatch, fnmatchcase
print(fnmatch('foo.txt', '*.txt'))

print(fnmatch('foo.txt', '?oo.txt'))


names = ['Dat1.csv', 'Dat2.csv', 'config.ini', 'foo.py']
print([name for name in names if fnmatch(name, 'Dat*.csv')])