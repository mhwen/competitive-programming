#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

void answer(string s) {
    cout << "! " << s << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    int a = -1, b = -1;
	    set<int> seen;
	    for(int i = 1; i <= n; i++) {
	        int x;
	        cin >> x;
	        if(x == 1)
	            a = i;
	        if(x == n)
	            b = i;
	        seen.insert(x);
	    }
	    if(sz(seen) == n) {
	        int r1 = query(a, b);
	        int r2 = query(b, a);
	        if(r1 != r2 || min(r1, r2) < n-1)
	            answer("A");
	        else
	            answer("B");
	    }
	    else {
	        int base = *seen.begin();
	        for(int i = 1; i <= n; i++) {
	            if(!seen.count(i)) {
	                int r = query(i, base);
	                if(r == 0)
	                    answer("A");
	                else
	                    answer("B");
	                break;
	            }
	        }
	    }
	}
}