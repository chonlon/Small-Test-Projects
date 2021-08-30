import re
from collections import Counter

with open('sanyrst.txt', 'r') as f:
    data = f.read()
    pattern = re.compile('Classname.*')
    result = pattern.findall(data)
    c = Counter(result)
    print(c.items())

