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

ll gcd(ll a, ll b) {
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

struct F {
	ll num, den;
	bool operator==(F f) const { return tie(num, den) == tie(f.num, f.den); }
	bool operator<(F f) const { return num*f.den < den*f.num; }
	bool operator<=(F f) const { return *this==f || *this<f; }
	F(ll n, ll d) {
		ll g = gcd(n, d);
		num = n/g;
		den = d/g;
	}
	F operator+(F f) const { return F(num*f.den+f.num*den, den*f.den); } 
	F operator-(F f) const { return F(num*f.den-f.num*den, den*f.den); } 
	F operator*(F f) const { return F(num*f.num, den*f.den); } 
	friend ostream& operator<<(ostream& os, F f) {
		return os << (long long)f.num << "/" << (long long)f.den; }
};

typedef pair<F, F> range;

bool inside(range r, F f) {
	return r.first <= f && f <= r.second;
}

pair<int, int> split(range r, F p) {
	F lo = r.first;
	F hi = r.second;
	F third = (hi-lo)*F(1, 3);
	range r1 = {lo, lo+third};
	range r2 = {lo+third+third, hi};
	if(inside(r1, p))
		return {0, 1};
	if(inside(r2, p))
		return {0, 2};
	return {1, 0};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int L;
	long long nx, dx, ny, dy, nz, dz;
	cin >> L >> nx >> dx >> ny >> dy >> nz >> dz;
	F x = F(nx, dx);
	F y = F(ny, dy);
	F z = F(nz, dz);
	
	range xr = {F(0, 1), F(1, 1)};
	range yr = {F(0, 1), F(1, 1)};
	range zr = {F(0, 1), F(1, 1)};
	bool good = true;
	
	auto fix = [](F f, int t) {
		if(t == 1)
			return f*F(3,1);
		else if(t == 2)
			return (f-F(2,3))*F(3,1);
		return (f-F(1,3))*F(3,1);
	};
	
	for(int i = 0; i < L; i++) {
		auto X = split(xr, x);
		auto Y = split(yr, y);
		auto Z = split(zr, z);
		if(X.first+Y.first+Z.first >= 2) {
			good = false;
			break;
		}
		x = fix(x, X.second);
		y = fix(y, Y.second);
		z = fix(z, Z.second);
	}
	if(good)
		cout << 1 << "\n";
	else
		cout << 0 << "\n";
}