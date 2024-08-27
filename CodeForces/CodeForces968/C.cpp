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
typedef long double ld;
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
		vector<int> freq(26);
		for(char c : s)
			freq[c-'a']++;
		for(int i = 0; i < n; i++) {
			auto it = max_element(all(freq));
			int pos = (int)(it-freq.begin());
			cout << (char)('a'+pos);
			freq[pos]--;
		}
		cout << "\n";
	}
}