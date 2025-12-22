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
	int n;
	ll c;
	cin >> n >> c;
	vector<ll> t(n), d(n);
	for(int i = 0; i < n; i++)
	    cin >> t[i] >> d[i];
	    
	ll perDay = min((ll)n, c);
	ll TimeNeeded = accumulate(all(t), 0LL);
	vector<__int128> cnts(n);
	vector<ll> overs(n);
	vector<ll> fulls(n);
	for(int i = 0; i < n; i++) {
	    overs[i] = t[i]%d[i];
	    fulls[i] = t[i]/d[i];
	}
	
	auto doable = [&](ll days) {
	    __int128 slots = (__int128)days*perDay;
        __int128 timeNeeded = TimeNeeded;
	    priority_queue<pair<pair<ll, ll>, int>> q;
	    for(int i = 0; i < n; i++) {
	        cnts[i] = 0;
	        q.push({{d[i], min(days, fulls[i])}, i});
	        if(fulls[i] < days) {
	            if(overs[i])
	                q.push({{overs[i], 1}, i});
	        }
	    }
	    while(slots > 0 && !q.empty()) {
	        auto [info, id] = q.top();
	        auto [D, amt] = info;
	        q.pop();
	        __int128 take = min((__int128)amt, slots);
	        timeNeeded -= D*take;
	        slots -= take;
	        cnts[id] += take;
	    }
	    __int128 lastDay = 0;
	    for(int i = 0; i < n; i++) {
	        if(cnts[i] == days)
	            lastDay++;
	    }
	    lastDay = max(lastDay, perDay-slots);
	    return timeNeeded <= c-lastDay;
	};
	
	ll l = 1, r = 1e15;
	ll ans = 1e15;
	while(l <= r) {
	    ll m = (l+r)/2;
	    if(doable(m)) {
	        ans = min(ans, m);
	        r = m-1;
	    }
	    else
	        l = m+1;
	}
	cout << ans-1 << "\n";
}