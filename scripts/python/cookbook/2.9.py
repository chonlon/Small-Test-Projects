import unicodedata

s1 = 'Spicy Jalape\u00f1o'
s2 = 'Spicy Jalapen\u0303o'
print(s1)
print(s2)

print(len(s1))
print(len(s2))

print(ascii(s1))
print(ascii(s2))

t1=unicodedata.normalize('NFC', s1)
t2=unicodedata.normalize('NFC', s2)

print(s1[12])
print(s2[13])