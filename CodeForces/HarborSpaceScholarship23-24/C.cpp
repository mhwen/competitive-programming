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
		int x;
		cin >> x;
		vector<int> ans;
		ans.push_back(x);
		for(int i = 2; i <= x; i*=2) {
			if(x%i != 0) {
				x -= i/2;
				ans.push_back(x);
			}
		}
		while(x > 1) {
			x/=2;
			ans.push_back(x);
		}
		cout << ans.size() << "\n";
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
	}
}