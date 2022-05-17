def texts():
    yield 'Is'
    yield 'Chicago'
    yield 'Not'
    yield 'Chicago'


def combine(source, maxsize):
    parts = []
    size = 0
    for part in source:
        parts.append(part)
        size += len(part)
        if size > maxsize:
            yield ''.join(parts)
            parts = []
            size = 0
        yield ''.join(parts)


parts = ['Is', 'Chicago', 'Not', 'Chicago?']
print(' '.join(parts))
print(','.join(parts))

print(' '.join(texts()))


with open('./files/2.14', 'w') as f:
    for part in combine(texts(), 32768):
        f.write(part)