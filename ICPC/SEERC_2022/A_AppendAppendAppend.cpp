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
	string s, t;
	cin >> s >> t;
	int n = (int)s.length();
	vector<vector<int>> next(s.length(), vector<int>(26, -1));
	s = s+s;
	vector<int> prev(26, -1);
	for(int i = 2*n-1; i >= 0; i--) {
		if(i < n) {
			for(int j = 0; j < 26; j++) {
				next[i][j] = prev[j]%n;
			}
		}
		prev[s[i]-'a'] = i;
	}
	int curr = prev[t[0]-'a'];
	int words = 1;
	for(int i = 1; i < (int)t.length(); i++) {
		int ne = next[curr][t[i]-'a'];
		if(ne <= curr)
		 	words++;
		curr = ne;
	}
	cout << words << "\n";
}