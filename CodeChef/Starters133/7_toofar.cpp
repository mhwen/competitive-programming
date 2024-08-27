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
constexpr ll MOD = 998244353;
#define sz(x) (int)(x).size()
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
		// assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

ll pow(ll a, ll b) {
	if(b == 0)
		return 1;
	ll res = pow(a, b/2);
	res = res*res%MOD;
	if(b%2==1)
		res = res*a%MOD;
	return res;
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<ll> fact(5e5+5);
	vector<ll> invFact(5e5+5);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < sz(fact); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	auto choose = [&](int a, int b) {
		return fact[a]*invFact[a-b]%MOD*invFact[b]%MOD;
	};
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> nums(n);
		vector<int> zeros(n+1);
		vector<int> left(n, -1);
		map<int, int> seen;
		for(int i = 0; i < n; i++) {
			zeros[i+1] = zeros[i];
			cin >> nums[i];
			if(nums[i] == 0) {
				zeros[i+1]++;
				continue;
			}
			if(!seen.count(nums[i]))
				seen[nums[i]] = -1;
			left[i] = seen[nums[i]];
			seen[nums[i]] = i;
		}
		RMQ rmq(left);
		ll res = 0;
		for(int M = max(1, sz(seen)); M <= min(n, m) && m-sz(seen) >= 0; M++) {
			bool bad = false;
			ll ways = choose(m-sz(seen), M-sz(seen));
			int i = 0;
			for(; i+M <= n; i+=M) {
				int L = rmq.query(i, i+M);
				if(L >= i) {
					bad = true;
					break;
				}
				int zero = zeros[i+M]-zeros[i];
				ways = ways*fact[zero]%MOD;
			}
			if(i < n) {
				int L = rmq.query(i, n);
				if(L >= i) {
					bad = true;
				}
				else {
					int zero = zeros[n]-zeros[i];
					int nonZero = n-i-zero;
					ways = ways*fact[M-nonZero]%MOD*invFact[M-(n-i)]%MOD;
				}
			}
			if(bad)
				continue;
			res += ways;
			res %= MOD;
		}
		cout << res << "\n";
	}
}

//every possible m from 1 to n
//check if every interval [1,m], [m+1, 2m], ... contains at most singles
//at the end check if total number of numbers is <= m
//then you can fill in how you want, choose remaining numbers then multiply by number of zeros in each segment