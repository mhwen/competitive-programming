#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <numeric>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

ll gcd(ll a, ll b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	//a = cx, b = dx
	//c and d coprime
	//dx*x = kcx + kdx for some k
	//dx = kc + kd
	//c + d divides dx
	//c, d coprime, so 
	//c + d divides x
	//c <= x, d <= x
	//so c^2 < n and d^2 < m
	//iterate over c and d
	//answer is number of values x st
	//cx <= n, dx <= m, and x divisible by c+d and c and d coprime
	
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		ll ans = 0;
		for(ll c = 1; c*c <= n; c++) {
			for(ll d = 1; d*d <= m; d++) {
				if(gcd(c, d) != 1)
					continue;
				ll topX = min(n/c, m/d);
				ans += topX/(c+d);
			}
		}
		cout << ans << "\n";
	}
}