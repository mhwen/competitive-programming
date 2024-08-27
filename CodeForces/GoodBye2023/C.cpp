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
		int n;
		cin >> n;
		ll sum = 0;
		ll odds = 0;
		for(int i = 0; i < n; i++) {
			ll val;
			cin >> val;
			sum += val;
			if(val%2==1)
				odds++;
			ll lost = odds/3;
			if(odds%3==1 && i != 0)
				lost++;
			cout << sum-lost << " ";
		}
		cout << "\n";
	}
}