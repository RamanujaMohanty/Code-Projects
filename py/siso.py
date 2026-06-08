VERBOSE  = True
def printV(text):
    if VERBOSE:
        print(f'L4() - VERBOSE: {text}')

DEV=False
def printD(text):
    if DEV:
        print(f'L4(): - DEV: {text}')


def L4(inString):

    int_strings = inString.split()
    pos_ints = []
    neg_ints = []

    # 1. Return 'no' if non-integer strings in input
    for s in int_strings:
        try:
            val = int(s)
            if val > 0:
                pos_ints.append(val)
            elif val < 0:
                neg_ints.append(val)
        except ValueError:
            return 'no'

    # 2 & 3. Return 'no' if no neg. ints or no pos. ints in input
    if not pos_ints or not neg_ints:
        return 'no'

    # 4. Return 'no' if (sum pos. ints % 3)/((sum neg. ints % 2) + 1) != 1/2
    sum_pos = sum(pos_ints)
    sum_neg = sum(neg_ints)

    d = (sum_pos % 3) / ((sum_neg % 2) + 1)

    if d == 0.5:
        return 'yes'
    else:
        return 'no'

if __name__ == '__main__':

    def test_case(F,string,expected,num,comment=''):
        err = '** '
        result = F(string)
        func_name = str(F).split()[1]
        func_call = f'''{func_name}("{string}")'''
        if result == expected: err = ''
        e = expected
        print (f'{err}test #{num} {func_call}: expected "{e}", received "{result}"')
        print (f'test #{num} Explanation: {comment}\n')
        return num + 1

    num = 1
    f = L4

    i =  ' -2 one 2'
    exp = 'one is not an integer'
    num = test_case(f,i,'no',num,exp)

    i =  ' 1 2'
    exp = 'no negatives in input'
    num = test_case(f,i,'no',num,exp)

    i =  '-1 -2'
    exp = 'no positives in input'
    num = test_case(f,i,'no',num,exp)

    i =  '4 -3 2'
    exp =  '(6 % 3)/((-3 % 2) + 1) = 0'
    num = test_case(f,i,'no',num,exp)

    i =  '2 -1  2 -2'
    exp =  '(4 % 3)/((-3 % 2) + 1) = 1/2'
    num = test_case(f,i,'yes',num,exp)

    # --- NEW TEST CASES ---

    # New Positive Test 1
    i = '4 -5'
    exp = '(4 % 3)/((-5 % 2) + 1) = 1/2'
    num = test_case(f,i,'yes',num,exp)

    # New Positive Test 2
    i = '7 -1'
    exp = '(7 % 3)/((-1 % 2) + 1) = 1/2'
    num = test_case(f,i,'yes',num,exp)

    # New Negative Test 1 (Math logic results in 0, not 1/2)
    i = '3 -1'
    exp = '(3 % 3)/((-1 % 2) + 1) = 0'
    num = test_case(f,i,'no',num,exp)

    # New Negative Test 2 (Contains a float instead of an integer)
    i = '5 -2 3.14'
    exp = '3.14 is not an integer'
    num = test_case(f,i,'no',num,exp)
