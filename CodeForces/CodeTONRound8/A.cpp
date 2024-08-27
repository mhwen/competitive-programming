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
		if(n == k) {
			for(int i = 1; i <= n; i++) 
				cout << 1 << " ";
			cout << "\n";
		}
		else if(k == 1) {
			for(int i = 1; i <= n; i++)
				cout << i << " ";
			cout << "\n";
		}
		else {
			cout << -1 << "\n";
		}
	}
}