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
		int n;
		cin >> n;
		int mx = 0;
		int mn = 1e9;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			mx = max(mx, a);
			mn = min(mn, a);
		}
		vector<int> moves;
		while(mn < mx) {
			if(mn%2==1 && mx%2==0) {
				moves.push_back(1);
				mn = (mn+1)/2;
				mx = (mx+1)/2;
			}
			else {
				moves.push_back(0);
				mn = mn/2;
				mx = mx/2;
			}
		}
		cout << (int)moves.size() << "\n";
		if(0 < (int)moves.size() && (int)moves.size() <= n) {
			for(int i : moves)
				cout << i << " ";
			cout << "\n";
		}
	}
}