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
	int tt;
	cin >> tt;
	while(tt-->0) {
		int n, m;
		cin >> n >> m;
		string s;
		string t;
		cin >> s;
		cin >> t;
		vector<queue<int>> nextChar(26);
		for(int i = 0; i < n; i++) {
			nextChar[s[i]-'a'].push(i);
		}
		string ans = "YES";
		vector<bool> used(n);
		for(char c : t) {
			if(nextChar[c-'a'].empty()) {
				ans = "NO";
				break;
			}
			int id = nextChar[c-'a'].front();
			nextChar[c-'a'].pop(); 
			for(int i = 0; i < c-'a'; i++) {
				while(!nextChar[i].empty() && nextChar[i].front() < id)
					nextChar[i].pop();
			}
		}
		cout << ans << "\n";
	}
}