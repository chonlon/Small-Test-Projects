s = slice(5, 50, 2)
print(s.start)
print(s.stop)
print(s.step)


print('*'*20)

str = 'HelloWorld'
# indices 将会缩放slice范围
print(*s.indices(len(str)))
