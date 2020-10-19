import re
num = re.compile(r'\d+')
print(num.match('123'))
print(num.match('\u0661\u0662\u0663'))
print(num.match('一二三'))


