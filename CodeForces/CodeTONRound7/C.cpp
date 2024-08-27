#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, x;
		cin >> n >> x;
		vector<int> a(n);
		vector<int> b(n);
		vector<pair<int, int>> sortedA(n);
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			sortedA[i] = {a[i], i};
		}
		for(int i = 0; i < n; i++) {
			cin >> b[i];
		}
		sort(sortedA.rbegin(), sortedA.rend());
		sort(b.begin(), b.end());
		vector<int> res(n);
		for(int i = 0; i < x; i++) {
			res[sortedA[x-1-i].second] = b[i];
		}
		for(int i = x; i < n; i++) {
			res[sortedA[n-1-i+x].second] = b[i];
		}
		int count = 0;
		for(int i = 0; i < n; i++) {
			if(a[i] > res[i])
				count++;
		}

		if(count == x) {
			cout << "YES\n";
			for(int i : res)
				cout << i << " ";
			cout << "\n";
		}
		else
			cout << "NO\n";
		
	}
}