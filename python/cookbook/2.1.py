line = 'asdf fjdk; afed,   fjek,asdf, foo'
import re
print(re.split(r'[;,\s]\s*', line))
field = re.split(r'(;|,|\s)\s*', line)
print(field)
values = field[::2]
delimiters = field[1::2] + ['']
print(values)
print(delimiters)
print(''.join(v + d for v, d in zip(values, delimiters)))


not_captured_field = re.split(r'(?:,|;|\s)\s*', line)
print(not_captured_field)