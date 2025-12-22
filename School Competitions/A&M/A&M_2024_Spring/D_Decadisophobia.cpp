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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;
	ll ee = 0;
	ll eo = 0;
	ll oe = 0;
	ll oo = 0;
	for(int i = 0; i < (int)n; i++) {
		ll x, y;
		cin >> x >> y;
		x = abs(x);
		y = abs(y);
		if(x%2==0 && y%2==0)
			ee++;
		else if(x%2==1 && y%2==1)
			oo++;
		else if(x%2==0 && y%2==1)
			eo++;
		else
			oe++;
	}
	ll good = n*(n-1)*(n-2)/6;
	good -= ee*oo*(eo+oe);
	good -= (ee+oo)*eo*oe;
	cout << good << "\n";
}