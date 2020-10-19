from collections import OrderedDict
import json

def ordereddict():
    d = OrderedDict()
    d['foo'] = 1
    d['bar'] = 2
    d['spam'] = 3
    d['grok'] = 4
    for key in d:
        print(key, d[key])
    return d

if __name__ == "__main__":
    d = ordereddict()
    print(json.dumps(d))

    unordered_dict = {
        'foo': 1,
        'bar': 2,
        'spam': 3,
        'grok':4
    }
    print(d)
    print(unordered_dict)
    print(json.dumps(unordered_dict))