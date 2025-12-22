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
		int n;
		cin >> n;
		string s;
		cin >> s;
		int lastS = -1;
		int firstP = n;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'p')
				firstP = min(i, firstP);
			if(s[i] == 's')
				lastS = i;
		}
		if(firstP < lastS)
			cout << "NO\n";
		else {
			int res = 0;
			for(int i = 1; i < n-1; i++) {
				if(s[i] == 'p')
					res |= 1;
				if(s[i] == 's')
					res |= 2;
			}
			if(res == 3)
				cout << "NO\n";
			else
				cout << "YES\n";
		}
	}
}