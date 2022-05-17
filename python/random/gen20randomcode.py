import random, string

class LengthError(ValueError):
   def __init__(self, arg):
      self.args = arg

def pad_zero_to_left(inputNumString, totalLength):
    '''
    takes inputNumString as input,
    pads zero to its left, and make it has the length totalLength
    1. calculates the length of inputNumString
    2. compares the length and totalLength
        2.1 if length > totalLength, raise an error
        2.2 if length == totalLength, return directly
        2.3 if length < totalLength, pads zeros to its left
    '''
    lengthOfInput = len(inputNumString)
    if lengthOfInput > totalLength:
        raise LengthError("The length of input is greater than the total\ length.")
    else:
        return '0' * (totalLength - lengthOfInput) + inputNumString

poolOfChars = string.ascii_letters + string.digits
random_codes = lambda x, y: ''.join([random.choice(x) for i in range(y)])

def invitation_code_generator(quantity, lengthOfRandom, LengthOfKey):
    '''
    generate `quantity` invitation codes
    '''
    placeHoldChar = "L"
    for index in range(quantity):
        tempString = ""
        try:
            yield random_codes(poolOfChars, lengthOfRandom) + placeHoldChar + \
                pad_zero_to_left(str(index), LengthOfKey)
        except LengthError:
            print("Index exceeds the length of master key.")

for invitationCode in invitation_code_generator(200, 16, 4):
    print(invitationCode)
