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
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> b(n-1);
		vector<int> a(n);
		for(int i = 0; i < n-1; i++) {
			cin >> b[i];
			a[i] |= b[i];
			a[i+1] |= b[i];
		}
		bool bad = false;
		for(int i = 0; i < n-1; i++) {
			if((a[i]&a[i+1]) != b[i])
				bad = true;
		}
		if(bad)
			cout << -1 << "\n";
		else {
			for(int i : a)
				cout << i << " ";
			cout << "\n";
		}
	}
}