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

using namespace std;
typedef __int128 ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll INF = 8e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		long long x, y, z, k;
		cin >> x >> y >> z >> k;
		
		auto check = [&](ll ups, ll attacks) {
			ll times = ups/k;
			if(times >= attacks) {
				times = attacks;
				ll rem = z-times*(times+1)/2*k;
				return rem <= 0;
			}
			ll rem = z-times*(times+1)/2*k;
			if(rem <= 0)
				return true;
			attacks -= times;
			if((rem+ups-1)/ups <= attacks)
				return true;
			return false;
		};
		
		//given m attacks, what is least number of upgrades needed to kill
		auto search = [&](ll m) {
			ll l = 1, r = 1e14;
			while(l <= r) {
				ll mid = (l+r)/2;
				if(check(mid, m))
					r = mid-1;
				else
					l = mid+1;
			}
			return l;
		};
		
		ll rem = z;
		ll cost = 0;
		ll best = INF;
		for(int i = 1; i <= 2e4+5; i++) {
			cost += x;
			if(i%k==0) {
				rem -= i;
				cost += y;
				rem = max((ll)0, rem);
			}
			best = min(best, cost+(rem+i-1)/i*y);
			if(rem == 0)
				break;
		}
		ll needed = z/(ll)1e4;
		while(needed > 0) {
			ll ups = search(needed);
			best = min(best, ups*x+needed*y);
			needed--;
		}
		cout << (long long)best << "\n";
	}
}