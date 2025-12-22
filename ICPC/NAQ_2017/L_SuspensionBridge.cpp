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

ld d, s;

ld Cosh(ld x) {
	return (exp(x)+exp(-x))/2;
}

ld Sinh(ld x) {
	return (exp(x)-exp(-x))/2;
}

ld eval(ld a) {
	ld left = a+s;
	ld right = a*Cosh(d/(2*a));
	return abs(right-left);
}

ld gss(ld a, ld b, ld (*f)(ld)) {
	ld r = (sqrt(5)-1)/2, eps = 1e-12;
	ld x1 = b - r*(b-a), x2 = a + r*(b-a);
	ld f1 = f(x1), f2 = f(x2);
	while(b-a > eps)
		if (f1 < f2) {
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
		}
	return a;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << fixed << setprecision(20);
	cin >> d >> s;
	ld a = gss(0, 2e9, eval);
	cout << 2*a*Sinh(d/(2*a)) << "\n";
}