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

struct ST {
    int n;
    vector<int> tree;
    ST(int _n) : n(_n), tree(2*n) {}
    ll query(int l, int r) {
        l += n;
        r += n;
        ll res = 0;
        while(l <= r) {
            if(l%2==1)
                res += tree[l++];
            if(r%2==0)
                res += tree[r--];
            l/=2;
            r/=2;
        }
        return res;
    }
    
    void update(int p) {
        p += n;
        while(p>0) {
            tree[p]++;
            p/=2;
        }
    }
};

ll count(vector<int>& a) {
    if(a.empty())
        return 0LL;
    int n = *max_element(all(a))+1;
    ST even(n);
    ST odd(n);
    ll inv = 0;
    for(int i = 0; i < sz(a); i++) {
        if(i%2==0) {
            inv += even.query(a[i], n-1);
            even.update(a[i]);
        }
        else {
            inv += odd.query(a[i], n-1);
            odd.update(a[i]);
        }
    }
    return inv;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    vector<int> evens;
	    vector<int> odds;
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        if(i%2==0)
	            evens.push_back(a[i]);
	        else
	            odds.push_back(a[i]);
	    }

	    sort(all(evens));
	    sort(all(odds));
	    reverse(all(evens));
	    reverse(all(odds));
	    vector<int> ans;
	    
	    for(int i = 0; i < n-4; i++) {
	        if(i%2==0) {
	            ans.push_back(evens.back());
	            evens.pop_back();
	        }
	        else {
	            ans.push_back(odds.back());
	            odds.pop_back();
	        }
	    }
	    ll inv = count(a);
	    ll F = count(ans);
	    
	    vector<vector<int>> rem;
	    for(int i = 0; i <= 1; i++) {
	        for(int j = 0; j <= 1; j++) {
	            vector<int> r{evens[i], odds[j], evens[i^1], odds[j^1]};
	            if(n%2==1)
	                reverse(all(r));
	            int me = 0;
	            if(r[0] > r[2])
	                me++;
	            if(r[1] > r[3])
	                me++;
	            if((me+F)%2==inv%2)
	                rem.push_back(r);
	        }
	    }
	    sort(all(rem));
	    ans.insert(ans.end(), all(rem[0]));
	    for(auto aa : ans)
	        cout << aa << " ";
	    cout << "\n";

	}
}