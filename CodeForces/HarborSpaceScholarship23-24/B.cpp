#include <iostream>
#include <vector>
#include <algorithm>

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
		vector<char> even;
		vector<char> odd;
		for(int i = 0; i < n; i++) {
			char c;
			cin >> c;
			if(i%2)
				even.push_back(c);
			else
				odd.push_back(c);
		}
		sort(even.begin(), even.end());
		sort(odd.begin(), odd.end());
		if(k%2) {
			for(int i = 0; i < n; i++) {
				if(i%2)
					cout << even[i/2];
				else
					cout << odd[i/2];
			}
			cout << "\n";
		}
		else {
			vector<char> ans;
			ans.insert(ans.end(), even.begin(), even.end());
			ans.insert(ans.end(), odd.begin(), odd.end());
			sort(ans.begin(), ans.end());
			for(int i = 0; i < n; i++) {
				cout << ans[i];
			}
			cout << "\n";
		}
		
	}
}