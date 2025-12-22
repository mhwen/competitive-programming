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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	ll k;
	cin >> n >> m >> k;
	vector<ll> kill(n+m+5);
	priority_queue<pair<ll, ll>> q;
	ll curr = 0;
	ll ans = 0;
	for(int i = 0; i < n+m; i++) {
	    ll f;
	    if(i < n)
	        cin >> f;
	    else
	        f = 0;
	    q.push({i, f});
	    curr -= kill[i];
	    while(curr < k && !q.empty()) {
	        auto [day, amt] = q.top();
	        q.pop();
	        if(day <= i-m)
	            continue;
	        ll take = min(k-curr, amt);
	        ll rem = amt-take;
	        if(day+m < sz(kill))
	            kill[day+m]+=take;
	        curr+=take;
	        ans+=take;
	        if(rem)
	            q.push({day, rem});
	    }
	}
	cout << ans << "\n";
}