#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n, x, p;
		cin >> n >> x >> p;
		ll b = ((n-x)+n)%n;
		bool good = false;
		for(ll i = 1; i <= min(p, 2*n); i++) {
			if(i*(i+1)/2%n == b)
				good = true;
		}
		if(good)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}