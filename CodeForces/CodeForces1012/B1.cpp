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
#define pb push_back
#define rep(i, a, b) for(int i = a; i < (b); ++i)

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n, k;
	    cin >> n >> k;
	    vector<ll> a(n), b(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i];
	    for(int i = 0; i < n; i++)
	        cin >> b[i];
	    reverse(all(a));
	    reverse(all(b));
	    for(int i = 0; i < n; i++) {
	        a.pb(a[i]);
	        b.pb(b[i]);
	    }
	    vector<ll> pa(sz(a)+1);
	    vector<ll> pb(sz(b)+1);
	    vector<ll> val(sz(a)+1);
	    for(int i = 0; i < sz(a); i++) {
	        pa[i+1] = pa[i]+a[i];
	        pb[i+1] = pb[i]+b[i];
	        val[i+1] = pa[i+1]-pb[i+1];
	    }
	    RMQ rmq(val);
	    int ans = 1;
	    for(int i = 0; i < n; i++) {
	        int id = i+n+1;
	        int l = id-n, r = id-1;
	        while(l <= r) {
	            int m = (l+r)/2;
	            if(val[id]-rmq.query(m, id) <= 0)
	                l = m+1;
	            else
	                r = m-1;
	        }
	        ans = max(ans, id-r);
	    }
	    cout << ans << "\n";
	    
	}
}