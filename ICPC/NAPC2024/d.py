from functools import lru_cache
from itertools import product

@lru_cache(maxsize=None)
def alice(state):
    for i, (a, b) in enumerate(state):
        if a > 0:
            for x in range(0, a):
                if b > 0 and (a-x) % 2 != b % 2:
                    continue
                state_cpy = list(state)
                state_cpy[i] = (x, b)
                if not bob(tuple(state_cpy)):
                    return True
    return False
            
@lru_cache(maxsize=None)
def bob(state):
    for i, (a, b) in enumerate(state):
        if a > 0:
            for x in range(0, a):
                state_cpy = list(state)
                state_cpy[i] = (x, b)
                if not alice(tuple(state_cpy)):
                    return True
    return False

def solve():
    n = int(input())
    As = [int(x) for x in input().split()]
    Bs = [int(x) for x in input().split()]

    state = list(map(list, zip(As, Bs)))

    b2 = sum(b == 2 for _, b in state)
    onemore = sum(a > 1 and b == 1 for a, b in state)

    if b2 + onemore > 1:
        print('Bob')
        return

    bobFirst = False
    if b2 == 1:
        for i in range(n):
            if state[i][1] == 2:
                if state[i][0] % 2 == 1:
                    print('Bob')
                    return
                state[i][0] = 0
                bobFirst = True

    if onemore == 1:
        for i in range(n):
            if state[i][1] == 1 and state[i][0] > 1:
                if state[i][0] % 2 == 0:
                    state[i][0] = 1
                else:
                    state[i][0] = 0
                bobFirst = True

    res = 0
    for a, _ in state:
        res ^= a
    
    if res != 0:
        if bobFirst:
            print('Bob')
        else:
            print('Alice')
    else:
        if bobFirst:
            print('Alice')
        else:
            print('Bob')

if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        solve()

'''        
cnt=0
tot=0
for st in product(product(range(1, 5), range(0, 3)), repeat=4):
    res = 0
    for a, _ in st:
        res ^= a
    # if True or any(a % 2 == 0 and b == 1 for a, b in st):

    if alice(st):
        print(st)
        cnt += 1
print(cnt)

print(alice(((1, 1),)))
    # print(st, alice(st))
'''