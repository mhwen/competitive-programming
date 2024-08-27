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
	int t;
	cin >> t;
	while(t-->0) {
		ll x, y;
		cin >> x >> y;
		ll slots = y+1;
		cout << max(x-2*y, (x+slots-1)/slots) << "\n";
	}
}