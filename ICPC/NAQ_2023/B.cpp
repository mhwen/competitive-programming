#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr ll MOD = 9302023;

bool match(string& s, int start, string& t) {
	for(int i = 0; i < (int)t.length(); i++) {
		if(s[i+start] != t[i])
			return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	vector<pair<int, ll>> dp(s.length()+1);
	vector<string> matches{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	dp[0] = {0, 1};
	for(int i = 1; i <= (int)s.length(); i++) {
		dp[i] = dp[i-1];
		
		for(string& m : matches) {
			int len = (int)m.length();
			if(i >= len && match(s, i-len, m)) {
				if(dp[i-len].first+len-1 > dp[i].first) {
					dp[i] = dp[i-len];
					dp[i].first += len-1;
				}
				else if(dp[i-len].first+len-1 == dp[i].first) {
					dp[i].second = (dp[i].second+dp[i-len].second)%MOD;
				}
			}
		}
	}
	cout << s.length()-dp[s.length()].first << "\n";
	cout << dp[s.length()].second << "\n";
}