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
		int k, x;
		ll a;
		cin >> k >> x >> a;
		ll spent = 0;
		bool pos = true;
		for(int i = 0; i <= x; i++) {
			ll cost = (spent+k-2)/(k-1);
			if(cost*(k-1)==spent)
				cost++;
			spent += cost;
			if(spent > a) {
				pos = false;
				break;
			}
		}
		if(pos)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}