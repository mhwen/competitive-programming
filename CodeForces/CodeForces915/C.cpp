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
		string newS = s;
		sort(newS.begin(), newS.end());
		vector<int> counts(26);
		for(char c : s)
			counts[c-'a']++;
		vector<int> positions;
		int curr = 'z';
		for(int i = 0; i < n; i++) {
			while(counts[curr-'a'] == 0)
				curr--;
			if(s[i] == curr)
				positions.push_back(i);
			counts[s[i]-'a']--;
		}
		int moves = 0;
		for(int i = 0; i < (int)positions.size()-1; i++) {
			if(s[positions[i]] != s[positions[i+1]]) {
				moves = (int)positions.size()-i-1;
				break;
			}
		}
		for(int i = 0; i < (int)positions.size()/2; i++) {
			swap(s[positions[i]], s[positions[positions.size()-i-1]]);
		}

		if(newS == s) {
			cout << moves << "\n";
		}
		else {
			cout << -1 << "\n";
		}
	}
}