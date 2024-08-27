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
	int n;
	string s;
	cin >> s;
	n = (int)s.length();
	
	auto good = [&](int left, int len) -> bool {
		vector<int> count(26);
		for(int i = 0; i < len; i++) {
			count[s[left+i]-'a']++;
			if(count[s[left+i]-'a'] > 2)
				return false;
		}
		for(int i = 0; i < len; i++) {
			if(s[left+i] != s[left+len-1-i])
				return false;
		}
		return true;
	};
	
	ll ans = 0;
	for(int len = 1; len <= min(55, (int)s.length()); len++) {
		for(int i = 0; i+len <= n; i++) {
			if(good(i, len)) {
				ans++;
			}
		}
	}
	
	cout << ans << "\n";
}