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
#include <cassert>

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
		string s;
		cin >> s;
		string res = "-1";
		for(int i = 0; i < sz(s)-1; i++) {
			if(s[i] == s[i+1])
				res = string({s[i], s[i+1]});
		}
		for(int i = 0; i < sz(s)-2; i++) {
			if(s[i] != s[i+1] && s[i] != s[i+2] && s[i+1]!=s[i+2])
				res = string({s[i], s[i+1], s[i+2]});
		}
		cout << res << "\n";
	}
}