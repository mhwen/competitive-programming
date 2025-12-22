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

int getSize(int n) {
    int res = 0;
    while(n > 0) {
        n/=3;
        res++;
    }
    return res;
}

int parity(int num) {
    int res = 0;
    while(num > 0) {
        res += num%3;
        num/=3;
    }
    return res%3;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    int bits = getSize(n-1);
	    auto dual = [&](int num) {
	        int res = 0;
	        int p = 1;
	        for(int i = 0; i < bits; i++) {
	            int v = num%3;
	            res += (3-v)%3*p;
	            p *= 3;
	            num/=3;
	        }
	        return res;
	    };
	    int id = 1;
	    map<int, int> ids;
	    
	    for(int i = 1; id < n; i++) {
	        if(ids.count(i*3+parity(i)))
	            continue;
	        int d = dual(i);
	        ids[i*3+parity(i)] = id;
	        ids[d*3+parity(d)] = id+1;
	        id+=2;
	    }
	    if(id == n)
	        ids[0] = id;
	    
	    vector<vector<int>> left(bits+1);
	    vector<vector<int>> right(bits+1);
	    for(auto [_mask, num] : ids) {
	        int mask = _mask;
	        for(int i = 0; i < bits+1; i++) {
	            if(mask%3==1)
	                left[i].push_back(num);
	            if(mask%3==2)
	                right[i].push_back(num);
	            mask/=3;
	        }
	    }
	    
	    cout << bits+1 << endl;
	    for(int i = 0; i < bits+1; i++) {
	        cout << sz(left[i])+sz(right[i]) << " ";
	        for(auto a : left[i])
	            cout << a << " ";
	        for(auto b : right[i])
	            cout << b << " ";
	        cout << endl;
	    }
	    
	    string s;
	    cin >> s;
	    for(auto [_mask, num] : ids) {
	        int mask = _mask;
	        int diff = 0;
	        for(int i = 0; i < bits+1; i++) {
	            int p = mask%3;
	            if(s[i] == 'L' && p != 1)
	                diff++;
	            if(s[i] == 'R' && p != 2)
	                diff++;
	            if(s[i] == 'N' && p != 0)
	                diff++;
	            mask/=3;
	        }
	        if(diff == 0) {
	            cout << num << endl;
	            break;
	        }
	    }
	    
	}
}