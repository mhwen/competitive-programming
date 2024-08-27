import sys
from random import randrange

# 1,34,179,143,84,209,106,218,157,1,46,246,83,186,237,73,190,239,118,154,190,208,189,131,131,179,110,36,124,143,15,91,252,47,199,150,82,121,112,205,56,99,84,214,97,96,220,141,117,250,116,225,147,57,13,121,73,222,173,76,184,199,74,210,169,150,57,156,61,151,223,95,95,225,219,18,245,77,229,78,204,200,170,144,118,237,143,220,74,116,250,210,73,124,56,106,84,141,1,91,199,169,214,246,76,208,186,190,47,156,57,117,184,121,73,205,112,82,84,131,199,15,173,225,222,179,190,83,150,239,99,57,110,121,13,36,209,131,154,218,147,252,97,61,46,157,150,96,189,50,241,118,150,78,61,240,64,59,30,48


input = sys.stdin.readline
# print = sys.stdout.write

MOD = 1000000007
POW = 257

pows = [pow(POW, i, MOD) for i in range(260)]

def main():
    lines = [s.strip() for s in sys.stdin.readlines()]
    line = ''.join(lines)
    lis = [int(x) for x in line.split(sep=",")]
        
    rolHash = 0
    
    lis = [randrange(256) for _ in range(10000)]
        
    for leng in range(min(256, len(lis)), 63, -1):
        print(leng)
        # freq = [0] * 256
        hsh = []
        for i in range(leng):
            # freq[lis[i]] += 1
            rolHash += pows[lis[i]]
            if rolHash >= MOD:
            	rolHash -= MOD
        
        hsh.append(rolHash)

        for i in range(0, len(lis)-leng):
            # freq[lis[i]] -= 1
            # freq[lis[i+leng]] += 1
            rolHash -= pows[lis[i]]
            rolHash += pows[lis[i+leng]]
            if rolHash < 0:
            	rolHash += MOD
            if rolHash >= MOD:
            	rolHash -= MOD
            
            hsh.append(rolHash)

        s = {}
        matches = []
        for i in range(len(hsh)):
            if i >= leng:
                if hsh[i-leng] not in s:
                    s[hsh[i-leng]] = i-leng
            if hsh[i] in s:
                matches.append((s[hsh[i]], i))
        if matches:
            m = min(matches)
            print(leng)
            print(m[0])
            print(m[1])
            return
    print('no key')
       	
if __name__ == '__main__':
    main()
