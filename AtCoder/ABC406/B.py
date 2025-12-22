import sys
import math
input = sys.stdin.readline
# print = sys.stdout.write

n, k = map(int, input().split(" "))

a = map(int, input().split(" "))

curr = 1
cap = 10**k

for num in a:
    curr = curr*num
    if curr >= cap:
        curr = 1
print(curr)
	