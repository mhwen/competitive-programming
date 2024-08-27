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
		string s;
		cin >> s;
		int ans = n-1;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'B')
				ans--;
			else
				break;
		}
		for(int i = n-1; i >= 0; i--) {
			if(s[i] == 'A')
				ans--;
			else
			break;
		}
		cout << max(0, ans) << "\n";
	}
}