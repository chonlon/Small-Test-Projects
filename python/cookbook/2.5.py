from calendar import month_abbr
import re

text = 'yeah, but no, but yeah, but no, but yeah'
print(text.replace('yeah', 'yep'))
text2 = 'Today is 11/27/2012. PyCon starts 3/13/2013.'


print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text2))
#       分别代表group3 1 2...------------^

datepat = re.compile(r'(\d+)/(\d+)/(\d+)')
def change_date(m):
    mon_name = month_abbr[int(m.group(1))]
    return '{} {} {}'.format(m.group(2), mon_name, m.group(3)[2:])
print(datepat.subn(change_date, text2))