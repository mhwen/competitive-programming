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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

ll myPow(ll a, ll b) {
	ll res = 1;
	ll p = a;
	while(b > 0) {
		if(b%2==1)
			res = res*p%MOD;
		p = p*p%MOD;
		b/=2;
	}
	return res;
}

struct V {
	ll odd;
	int twos;
	V() {odd = 1; twos = 0;}
	V(ll num) {
		twos = 0;
		while(num%2==0) {
			twos++;
			num/=2;
		}
		odd = num;
	}
	V(ll o, int t) : odd(o), twos(t) {}
	bool operator<(V v) const {
		int diff = 0;
		ll a = odd;
		ll b = v.odd;
		while(a < b) {
			a*=2;
			diff--;
		}
		while(b < a) {
			b*=2;
			diff++;
		}
		diff += twos-v.twos;
		if(diff == 0)
			return a < b;
		return diff < 0;
	}
	ll eval() {
		return odd*myPow(2, twos)%MOD;
	}
	friend ostream& operator<<(ostream& os, V v) {
		ll val = v.odd;
		for(int i = 0; i < v.twos; i++)
			val *= 2;
		return os << val; }
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		stack<V> s;
		ll res = 0;
		for(int i = 0; i < n; i++) {
			ll val;
			cin >> val;
			V v(val);
			while(!s.empty() && V(s.top().odd) < v) {
				V add = s.top();
				s.pop();
				v.twos += add.twos;
				res = (res-add.eval()+MOD)%MOD;
				add.twos = 0;
				res = (res+add.eval())%MOD;
			}
			res = (res+v.eval())%MOD;
			s.push(v);
			cout << res << " ";
		}
		cout << "\n";
	}
}