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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	ll straw;
	cin >> straw;
	int n;
	cin >> n;
	vector<ll> sticks(n);
	for(int i = 0; i < n; i++)
	    cin >> sticks[i];
	ll brick;
	int m;
	cin >> brick >> m;
	vector<ll> B(m);
	for(int i = 0; i < m; i++)
	    cin >> B[i];
	int bi = 0;
	vector<ll> best(t+1);
	best[0] = 0;
	ll id = 0;
	while(id+brick < sz(best)) {
	    best[id+brick] = best[id]+3;
	    id += brick;
	    brick += B[bi++];
	    bi %= sz(B);
	}
	for(int i = 1; i < sz(best); i++) {
	    best[i] = max(best[i], best[i-1]);
	    if(i-straw >= 0)
	        best[i] = max(best[i], best[i-straw]+1);
	}
    ll res = best[t];
    ll rem = t;
    int si = 0;
    ll curr = 0;
    while(rem-sticks[si] >= 0) {
        rem -= sticks[si];
        curr += 2;
        si = (si+1)%sz(sticks);
        res = max(res, curr+best[rem]);
    }
    cout << res << "\n";
	
}