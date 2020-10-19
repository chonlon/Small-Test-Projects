import re


text = 'yeah, but no, but yeah, but no, but yeah'
print(text == 'yeah')
print(text.startswith('yeah'))
print(text.find('no'))

text1 = '11/27/2012'
text2 = 'Nov 27, 2012'

if re.match(r'[0-9]+/[0-9]+/[0-9]+',text1):
    print('yes')
else:
    print('no')

var = re.search(r'\d+', text2)
if var:
    print('search first one: ',text2[var.start():var.end()])

datepat = re.compile(r'(\d+)/(\d+)/(\d+)')
if datepat.match(text1):
    print('yes')
else:
    print('no')

m = datepat.match('11/27/2020')
for i in range(0,4):
    print(m.group(i))

print(m.groups())


text3 = 'Today is 11/27/2012. PyCon starts 3/13/2013.'
for month, day, year in datepat.findall(text3):
    print('{}-{}-{}'.format(year, month, day))
