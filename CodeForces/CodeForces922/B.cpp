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
		vector<int> a(n);
		vector<int> b(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
		}
		for(int i = 0; i < n; i++) {
			cin >> b[i];
		}
		vector<int> m(n+1);
		for(int i = 0; i < n; i++) {
			m[b[i]] = a[i];
		}
		sort(b.begin(), b.end(), [&](int x, int y) {
			return m[x] < m[y];
		});
		for(int i = 0; i < n; i++) {
			cout << i+1 << " ";
		}
		cout << "\n";
		for(int i = 0; i < n; i++) {
			cout << b[i] << " ";
		}
		cout << "\n";
	}
}