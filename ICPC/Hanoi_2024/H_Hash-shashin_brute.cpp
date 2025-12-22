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

string slow(int n, int m, string s) {
	string res(n, '-');
	for(int start = 0; start < (1<<n); start++) {
		int curr = 0;
		bool good = true;
		for(int bit = 0; bit < n; bit++) {
			int prev = curr;
			if(start&(1<<bit))
				curr = (curr*2+1)%m;
			else
				curr = (curr*2)%m;
			if(s[bit] == '=' && prev != curr) {
				good = false;
				break;
			}
			if(s[bit] == '<' && prev >= curr) {
				good = false;
				break;
			}
			if(s[bit] == '>' && prev <= curr) {
				good = false;
				break;
			}
		}
		if(good) {
			for(int bit = 0; bit < n; bit++) {
				char me;
				if(start&(1<<bit))
					me = '1';
				else
					me = '0';
				if(res[bit] != '-' && res[bit] != me)
					res[bit] = '?';
				else
					res[bit] = me;
			}
		}
	}
	if(res[0] == '-')
		res = "impossible";
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		string s;
		cin >> s;
		cout << slow(n, m, s) << "\n";
	}
}