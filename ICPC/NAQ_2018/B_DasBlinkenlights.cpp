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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll p, q, s;
	cin >> p >> q >> s;
	ll val = p*q/gcd(p, q);
	if(val <= s)
		cout << "yes\n";
	else
		cout << "no\n";
}