text='Hello World'
print(text.ljust(20, '-'))
print(text.rjust(20, '+'))
print(text.center(20))

print('{:>10s} {:>10s}'.format('Hello', 'World'))