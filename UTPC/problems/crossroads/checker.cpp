#include "testlib.h"
#include <set>
#include <stack>
#include <vector>
 
using namespace std;
 
bool checkValid(vector<pair<int, int>> p, int n) {
	set<int> seen;
	vector<int> paired(n, -1);
	for(auto [a, b] : p) {
		if(seen.count(a) || seen.count(b))
			return false;
		seen.insert(a);
		seen.insert(b);
		paired[a-1] = b-1;
		paired[b-1] = a-1;
	}
	stack<int> s;
	set<int> active;
	for(int I = 0; I < 4*n; I++) {
		int i = I%n;
		if(paired[i] == -1)
			continue;
		int other = paired[i];
		if(!active.count(other)) {
			active.insert(i);
			s.push(i);
		}
		else {
			if(s.empty() || s.top() != other)
				return false;
			s.pop();
			active.erase(other);
		}
	}
	return true;
}
 
int main(int argc, char * argv[])
{
    setName("check construction is valid and complete");
 
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int ans_r = ans.readInt();
    int out_r = ouf.readInt();
    if(ans_r != out_r)
        quitf(_wa, "number of rounds is not optimal");

    set<pair<int, int>> seen;
    for(int i = 0; i < ans_r; i++) {
        int m = ouf.readInt(0, n);
        if(m < 0 || m > n)
            quitf(_wa, "construction is invalid - on round %d, expected: 0<=m<=%d found: m=%d ", i+1, n, m);
        
        vector<pair<int, int>> p;
        for(int j = 0; j < m; j++) {
            int a = ouf.readInt(1, n);
            int b = ouf.readInt(1, n);
            if(a == b)
                quitf(_wa, "construction is invalid - on round %d, invalid indices given: %d %d", i+1, a, b);
            if(a > b)
                swap(a, b);
            seen.insert({a, b});
            p.emplace_back(a, b);
        }
        if(!checkValid(p, n))
            quitf(_wa, "construction is invalid - on round %d, found intersecting pairs or person in multiple pairs", i+1);
    }
    if((int)seen.size() != n*(n-1)/2)
        quitf(_wa, "construction is incomplete - not all pairs of people made an exchange");
 
    if (!ouf.seekEof())
        quitf(_wa, "extraneous output in construction");
    
    quitf(_ok, "good job you solved it");
}
