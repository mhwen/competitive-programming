from itertools import combinations
import sys

input = sys.stdin.readlines()

m, k, c = map(int, input[0].split())
keys = list(combinations(range(m), k))

def conv(row):
    return [int(x) for x in row[1:-1].split(' ')]

chords = list(conv(row) for row in input[1:])

curset = set()
ans = [' '] * len(chords)
last = 0
curKey = -1

print
for i in range(len(chords)):
    curset = curset.union(set(chords[i]))
    if len(curset) == k:
        curKey = keys.find(tuple(curset))
        for j in range(last, i+1):
            ans[j] = curKey
        last=i+1
    elif len(curset) > k:
        if curKey == -1:
            for j in range(last, i):
                ans[j] = '?'
        last=i
        curset = set(chords[i])

for j in range(last, len(chords)):
    ans[j] = '?' if curKey == -1 else curKey

print('\n'.join(ans))