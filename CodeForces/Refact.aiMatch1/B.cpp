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
		string s, r;
		cin >> s >> r;
		int o = 0, z = 0;
		for(char c : s) {
			if(c == '0')
				z++;
			else
				o++;
		}
		bool good = true;
		for(char c : r) {
			if(o == 0 || z == 0)
				good = false;
			if(c == '0')
				o--;
			else
				z--;
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}