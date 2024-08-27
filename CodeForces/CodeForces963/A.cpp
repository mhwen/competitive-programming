#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

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
		vector<int> counts(4);
		int score = 0;
		for(char c : s)
			if(c != '?')
				counts[c-'A']++;
		for(int i = 0; i < 4; i++)
			score += min(n, counts[i]);
		cout << score << "\n";
	}
}