from collections import namedtuple
Subscriber = namedtuple('Subscriber', ['addr', 'joined'])
sub = Subscriber('jonesy@example.com', '2012-10-19')
print(sub)
print(sub.addr)
print(sub.joined)
print(len(sub))

# def compute_cost(records):
#     total = 0.0
#     for rec in records:
#         total += rec[1] * rec[2]

#     return total

# common_tup = tuple([[100, 123.5]])
# print(compute_cost(common_tup))