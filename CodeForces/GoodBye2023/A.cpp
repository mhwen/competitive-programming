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
		int n, k;
		cin >> n >> k;
		ll val = 1;
		for(int i = 0; i < n; i++) {
			ll b;
			cin >> b;
			val = val*b;
		}
		if(2023%val != 0) {
			cout << "NO\n";
		}
		else {
			cout << "YES\n";
			cout << 2023/val;
			for(int i = 0; i < k-1; i++)
				cout << " " << 1;
			cout << "\n";
		}
	}
}