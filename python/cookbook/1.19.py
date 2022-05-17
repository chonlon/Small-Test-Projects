nums = [1, 2, 3, 4, 5]
s = sum(x * x for x in nums)

import os
files = os.listdir('.')
if any(name.endswith('.py') for name in files):
    print('There be python!')
else:
    print('Sorry, no python')

s = ('ACME', 50, 123.45)
print(','.join(str(x) for x in s))
