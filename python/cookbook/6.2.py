import json
with open('.vscode/settings.json', 'r') as f:
    data = json.load(f)
    datas = json.loads(f)
    print(data)
    print(datas)

d = {'a': True,
     'b': 'Hello',
     'c': None}

with open('files/d.json', 'w') as f:
    json.dump(d, f)
