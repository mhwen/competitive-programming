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

ld X1, Y1, X2, Y2, A;
ld X, Y;

ld dist(ld x, ld y, ld x2, ld y2) {
	ld dx = x-x2;
	ld dy = y-y2;
	return sqrt(dx*dx+dy*dy);
}

ld checkX(ld x) {
	ld d = dist(x, Y, X1, Y1)+dist(x, Y, X2, Y2);
	return d-A;
}
ld checkY(ld y) {
	ld d = dist(X, y, X1, Y1)+dist(X, y, X2, Y2);
	return d-A;
}

ld gss(ld a, ld b, ld (*f)(ld)) {
	ld r = (sqrt(5)-1)/2, eps = 1e-11;
	ld x1 = b - r*(b-a), x2 = a + r*(b-a);
	ld f1 = f(x1), f2 = f(x2);
	while (b-a > eps)
		if (f1 < f2) { //change to > to find maximum
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
	cin >> X1 >> Y1 >> X2 >> Y2 >> A;
	A/=2;
	ld loX = 1e9, hiX = -1e9, loY = 1e9, hiY = -1e9;
	
	auto clamp = [&](ld x, ld y) {
		hiX = max(hiX, x);
		loX = min(loX, x);
		hiY = max(hiY, y);
		loY = min(loY, y);
	};
	
	//big X
	ld l = max(X1, X2), r = 1e9;
	for(int i = 0; i < 200; i++) {
		ld mid = (l+r)/2;
		X = mid;
		ld y = gss(-1e9, 1e9, checkY);
		ld d = checkY(y);
		if(d-A <= 0) {
			clamp(X, y);
			l = mid;
		}
		else
			r = mid;	
	}
	//small X
	l = -1e9, r = min(X1, X2);
	for(int i = 0; i < 200; i++) {
		ld mid = (l+r)/2;
		X = mid;
		ld y = gss(-1e9, 1e9, checkY);
		ld d = checkY(y);
		if(d-A <= 0) {
			clamp(X, y);
			r = mid;
		}
		else
			l = mid;	
	}
	//big Y
	l = max(Y1, Y2), r = 1e9;
	for(int i = 0; i < 200; i++) {
		ld mid = (l+r)/2;
		Y = mid;
		ld x = gss(-1e9, 1e9, checkX);
		ld d = checkX(x);
		if(d-A <= 0) {
			clamp(x, Y);
			l = mid;
		}
		else
			r = mid;	
	}
	//small Y
	l = -1e9, r = min(Y1, Y2);
	for(int i = 0; i < 200; i++) {
		ld mid = (l+r)/2;
		Y = mid;
		ld x = gss(-1e9, 1e9, checkX);
		ld d = checkX(x);
		if(d-A <= 0) {
			clamp(x, Y);
			r = mid;
		}
		else
			l = mid;	
	}
	cout << fixed << setprecision(20) << loX << " " << loY << " " << hiX << " " << hiY << "\n";
	
}