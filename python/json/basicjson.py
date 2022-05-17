import json

def simple_serialize(data):
    json_str = json.dumps(data)
    return json_str

def serialize_instance(obj):
    d = {'__classname__': type(obj).__name__ }
    d.update(vars(obj))
    return d

data = {
    'a':True,
    'b':'Hello',
    'c':None
}

print(simple_serialize(data))
#print(serialize_instance(simple_serialize))
