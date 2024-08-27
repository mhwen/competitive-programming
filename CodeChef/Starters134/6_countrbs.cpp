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
typedef long long ll;
#define sz(x) (int)(x).size()
constexpr ll MOD = 31443539979727;
constexpr ll P = 31;
constexpr ll P2 = 11;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		vector<ll> hash(n+1);
		vector<ll> pow(n+1);
		vector<ll> hash2(n+1);
		vector<ll> pow2(n+1);
		pow[0] = pow2[0] = 1;
		for(int i = 1; i <= n; i++) {
			int val = s[i-1] == '(' ? 1 : 2;
			hash[i] = hash[i-1]*P%MOD+val;
			hash[i] %= MOD;
			pow[i] = pow[i-1]*P%MOD;
			
			hash2[i] = hash2[i-1]*P2%MOD+val;
			hash2[i] %= MOD;
			pow2[i] = pow2[i-1]*P2%MOD;
		}
		auto getHash = [&](int l, int r) {
			ll res = (hash[r]-hash[l]*pow[r-l]%MOD+MOD)%MOD;
			return res;
		};
		auto getHash2 = [&](int l, int r) {
			ll res = (hash2[r]-hash2[l]*pow2[r-l]%MOD+MOD)%MOD;
			return res;
		};
		stack<pair<char, int>> st;
		map<pair<ll, ll>, ll> counts;
		for(int i = 0; i < n; i++) {
			if(st.empty())
				st.push({s[i], i});
			else {
				if(st.top().first == '(' && s[i] == ')') {
					int l = st.top().second;
					st.pop();
					ll h1 = getHash(l, i+1);
					ll h2 = getHash2(l, i+1);
					counts[{h1, h2}]++;
					// cout << "added " << l << " " << i << endl;
				}
				else {
					st.push({s[i], i});
				}
			}
		}
		ll ans = 0;
		for(auto[_, cnt] : counts) {
			ans += cnt*(cnt-1)/2;
		}
		cout << ans << "\n";
	}
}