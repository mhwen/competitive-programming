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
#include <random>
#include <chrono>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll randval(ll n) {
	return uniform_int_distribution(1LL, n)(rng);
}

ll MOD = randval(2e9);

constexpr ll P = 31;
constexpr int INF = 1e6;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		int first = sz(s);
		int last = -1;
		for(int i = 0; i < sz(s); i++) {
			if(s[i] != 'a') {
				first = min(first, i);
				last = i;
			}
		}
		if(last == -1) {
			cout << sz(s)-1 << "\n";
			continue;
		}
		ll startA = first;
		ll endA = sz(s)-last-1;
		// cout << startA << " s e " << endA << endl;
		s = s.substr(first, last-first+1);
		int n = sz(s);
		vector<ll> hash(n+1);
		vector<ll> pows(n+1);
		pows[0] = 1;
		for(int i = 0; i < n; i++) {
			hash[i+1] = (hash[i]*P%MOD + (s[i]-'a'+1))%MOD;
			pows[i+1] = pows[i]*P%MOD;
		}
		//[a, b)
		auto get = [&](int a, int b) {
			if(b > n)
				return -1LL;
			return (hash[b]-hash[a]*pows[b-a]%MOD+MOD)%MOD;
		};
		
		auto check = [&](int I) {
			// cout << "checking " << s.substr(0, I+1) << endl;
			ll H = get(0, I+1);
			int aGap = INF;
			int aCount = 0;
			for(int i = I+1; i < n; i++) {
				if(s[i] != 'a') {
					ll otherH = get(i, i+I+1);
					if(otherH != H) {
						// cout << "failed at " << i << " " << s.substr(i, I+1) << endl;
						return -1;
					}
					aGap = min(aGap, aCount);
					i += I;
					aCount = 0;
				}
				else
					aCount++;
			}
			return aGap;
		};
		
		ll ans = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'a')
				continue;
			ll mids = check(i);
			// cout << s.substr(0, i+1) << " has gap " << mids << endl;
			if(mids >= startA+endA) {
				ans += (startA+1)*(endA+1);
			}
			else {
				for(ll start = 0; start <= startA; start++) {
					ll rem = mids-start;
					if(rem < 0)
						break;
					ans += min(rem, endA)+1;
				}
			}
		}
		cout << ans << "\n";
		
		
	}
	

}