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
		int x, y, n;
		cin >> x >> y >> n;
		int amount = 1;
		int curr = y;
		vector<int> ans;
		for(int i = 0; i < n-1; i++) {
			ans.push_back(curr);
			curr -= amount;
			amount++;
		}
		ans.push_back(x);
		if(curr < x)
			cout << -1 << "\n";
		else {
			for(int i = n-1; i >= 0; i--) {
				cout << ans[i] << " ";
			}
			cout << "\n";
		}
	}
}