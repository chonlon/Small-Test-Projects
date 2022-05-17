def frange(start, stop, increment):
    x = start
    while x < stop:
        yield x
        x += increment

def doTestFrange():
    for n in frange(0, 4, 0.5):
        print(n)

def countdown(n):
    print('Starting to count from', n)
    while n > 0:
        yield n
        n -= 1
    print('Done!')

def doTestCountdown():
    c = countdown(4)
    for _ in range(5):
        try:
            print('*'*20)
            print(next(c))
        except StopIteration:
            pass

if __name__ == '__main__':
    doTestFrange()
    doTestCountdown()