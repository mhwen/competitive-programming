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

vector<ll> get(vector<ll>& a) {
    vector<ll> res(sz(a)+1);
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<ll>> hi;
    ll curr = 0;
    auto add = [&](ll v) {
          curr += v;
          hi.push(v);
          while(sz(hi) > sz(lo)) {
              curr -= 2*hi.top();
              lo.push(hi.top());
              hi.pop();
          }
          while(!hi.empty() && hi.top() < lo.top()) {
              ll H = hi.top();
              ll L = lo.top();
              curr += 2*L-2*H;
              hi.pop();
              lo.pop();
              hi.push(L);
              lo.push(H);
          }
    };
    for(int i = 2; i < sz(res); i+=2) {
        add(a[i-1]);
        add(a[i-2]);
        res[i] = curr;
    }
    return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> a(n);
	for(int i = 0; i < n; i++) {
	    cin >> a[i];
	}
	if(n%2==0) {
	    sort(all(a));
	    ll ans = 0;
	    for(int i = 0; i < n/2; i++)
	        ans -= a[i];
	    for(int i = n/2; i < n; i++)
	        ans += a[i];
	    cout << ans << "\n";
	}
	else {
	    auto left = get(a);
	    reverse(all(a));
	    auto right = get(a);
	    reverse(all(right));
	    ll best = 0;
	    for(int i = 0; i < n; i+=2) {
	        best = max(best, left[i]+right[i+1]);
	    }
	    cout << best << "\n";
	}
}