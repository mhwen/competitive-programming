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
	string line;
	while(getline(cin, line)) {
		int n = stoi(line);
		set<string> seen;
		for(int i = 0; i < n; i++) {
			string s;
			cin >> s;
			sort(all(s));
			s.erase(unique(all(s)), s.end());
			seen.insert(s);
		}
		cout << sz(seen) << endl;
		getline(cin, line);
	}
}