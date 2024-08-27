#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

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

struct Fraction {
	ll top, bottom;
	Fraction() : top(0), bottom(1) {}
	Fraction(ll t, ll b) : top(t), bottom(b) {}
	Fraction operator+(const Fraction& a) const {
		return Fraction((top*a.bottom%MOD+a.top*bottom%MOD)%MOD, bottom*a.bottom%MOD);
	}
	Fraction operator*(const Fraction& a) const {
		return Fraction(top*a.top%MOD, bottom*a.bottom%MOD);
	}
	Fraction operator*(const ll& a) const {
		return Fraction(top*a%MOD, bottom);
	}
	ll show() {
		return top*inv(bottom)%MOD;
	}
};

int main() {
	
	vector<ll> fact(5000);
	vector<ll> invFact(5000);
	fact[0] = invFact[0] = 1;
	for(int i = 1; i < (int)fact.size(); i++) {
		fact[i] = fact[i-1]*i%MOD;
		invFact[i] = inv(fact[i]);
	}
	
	function<Fraction(ll, ll)> choose = [&](ll a, ll b) {
		return Fraction(fact[a], fact[a-b]*fact[b]%MOD);
	};
	
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<Fraction> dp(n);
	dp[0] = Fraction(1, 1);
	for(int i = 1; i < n; i++) {
		for(int j = 0; j < i; j++) {
			dp[i] = dp[i]+choose(i, j)*dp[j];
		}
		dp[i] = dp[i]*Fraction(1, (pow(2, i+1)-1+MOD)%MOD);
	}
	for(int i = 0; i < n; i++) {
		Fraction chance;
		for(int j = 0; j <= i; j++) {
			chance = chance+choose(i, j)*dp[n-j-1];
		}
		chance = chance*Fraction(1, pow(2, i));
		cout << chance.show() << " ";
	}
	cout << "\n";
}