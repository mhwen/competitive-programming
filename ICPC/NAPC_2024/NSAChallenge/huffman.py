from dataclasses import dataclass
from typing import Any
import heapq
import sys

input = sys.stdin.readline
print = sys.stdout.write

@dataclass(order=True)
class Node:
    c: int
    left: Any 
    right: Any

def extract(tree, path):
    if tree.left == None:
        return [(tree.c, path)]
    else:
        l = tree.left
        r = tree.right
        return extract(l, path + '0') + extract(r, path + '1')
        
def add_one(str):
    num = int(str, 2)
    num += 1
    res = bin(num)[2:]
    while len(res) < len(str):
        res = '0' + res
    return res
        
def canonicalize(data):
    def cmp(c):
        return (len(c[1]), c[0])
    data.sort(key=cmp)

    cur = ''
    res = []
    for c, path in data:
        if len(cur) == 0:
            cur = '0' * len(path)
        else:
            cur = add_one(cur)
            while len(cur) < len(path):
                cur += '0'
        res += [(c, cur)]
    return res


def compress(s):
    counts = {}
    for c in s:
        counts[c] = counts.get(c, 0) + 1

    pq = []
    for c, cnt in counts.items():
        heapq.heappush(pq, (cnt, Node(ord(c), None, None)))

    while len(pq) > 1:
        item1 = heapq.heappop(pq)
        item2 = heapq.heappop(pq)

        new_cnt = item1[0] + item2[0]
        new_item = Node(0, item1[1], item2[1])
        heapq.heappush(pq, (new_cnt, new_item))

    tree = pq[0][1]
    data = extract(tree, '')
    data = canonicalize(data)

    length = f'{len(data):02X}'
    pairs = ''
    dd = {}
    for c, path in data:
        pairs += f'{c:02X}'
        pairs += f'{len(path):02X}'
        dd[c] = path

    encoding = ''.join(dd[ord(c)] for c in s)

    k = f'{len(encoding):08X}'

    while len(encoding) % 8 != 0:
        encoding += '0'
    encoding_hex = []
    for i in range(0, len(encoding), 8):
        num = int(encoding[i:i+8], 2)
        encoding_hex.append(f'{num:02X}')

    print(length)
    print(pairs)
    print(k)
    print(''.join(encoding_hex))
    print('\n')

mp = {
    '0': '0000',
    '1': '0001',
    '2': '0010',
    '3': '0011',
    '4': '0100',
    '5': '0101',
    '6': '0110',
    '7': '0111',
    '8': '1000',
    '9': '1001',
    'A': '1010',
    'B': '1011',
    'C': '1100',
    'D': '1101',
    'E': '1110',
    'F': '1111',
}

def decompress(s):
    length = int(s[:2], 16)
    
    i = 2
    data = []
    for _ in range(length):
        c = int(s[i:i+2], 16)
        i += 2
        len1 = int(s[i:i+2], 16)
        i += 2

        data += [(c, '0'*len1)]
    data = canonicalize(data)

    k = int(s[i:i+8], 16)
    i += 8

    # encode the rest
    encoding = ''.join(mp[c] for c in s[i:])
    encoding = encoding[:k]

    i = 0
    res = []
    while i < k:
        for c, path in data:
            if i + len(path) <= k and encoding[i:i+len(path)] == path:
                res.append(chr(c))
                i += len(path)
                break

    print(''.join(res) + '\n')

def main():
    typ = input()[:-1]
    s = input()[:-1]

    if typ == 'COMPRESS':
        compress(s)
    else:
        decompress(s)

if __name__ == '__main__':
    main()
