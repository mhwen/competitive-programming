#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

ll pow(ll a, ll b) {
	if(b==0)
		return 1;
	ll res = pow(a, b/2);
	res=res*res%MOD;
	if(b%2)
		res=res*a%MOD;
	return res;	
}

ll inv(ll a) {
	return pow(a, MOD-2);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	function<ll(int, int)> choose = [](int a, int b) {
		if(a < 0 || b < 0)
			return 0LL;
		ll val = 1;
		for(int i = 0; i < b; i++) {
			val = val*(a-i)%MOD;
			val = val*inv(i+1)%MOD;
		}
		return val;
	};
	int t;
	cin >> t;
	while(t-->0) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if(a == b && a == 0) {
			if(c > 0 && d > 0)
				cout << 0 << "\n";
			else
				cout << 1 << "\n";
		}
		else if(abs(a-b) > 1)
			cout << 0 << "\n";
		else if(abs(a-b) == 1) {
			if(a < b)
				swap(a, b);
			ll res1 = choose(a+c-1, a-1);
			ll res2 = choose(a+d-1, a-1);
			cout << res1*res2%MOD << "\n";
		}
		else {
			ll res1 = choose(a+c-1, a-1);
			ll res2 = choose(b+d, b);
			ll res3 = choose(a+c, a);
			ll res4 = choose(b+d-1, b-1);
			cout << (res1*res2%MOD+res3*res4%MOD)%MOD << "\n";
		}
	}
}