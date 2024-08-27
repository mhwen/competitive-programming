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
	int n, m;
	cin >> n >> m;
	int best = 0;
	int row = -1, col = -1;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for(int j = 0; j < m; j++) {
			char c = s[j];
			if('1' <= c && c <= '9' && c-'0' > best) {
				best = c-'0';
				row = i+1;
				col = j+1;
			}
		}
	}
	cout << row << " " << col << "\n";
}