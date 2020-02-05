def fab(time : int):
    if time == 0:
        return 0
    if time == 1:
        return 1
    return fab(time - 1) + fab(time - 2)

def fab2(time : int):
    i = 1
    a, b =  0, 1
    while i < time:
        i = i + 1
        a, b = b, a + b
    return b

if __name__ == "__main__":
    num = int(input("please input a num to calculate:"))
    print("the result we calculate1:", fab(num))
    print("the result we calculate2:", fab2(num))