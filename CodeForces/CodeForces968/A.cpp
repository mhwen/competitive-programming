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
		bool good = false;
		for(int i = 1; i < n; i++) {
			string a = s.substr(0, i);
			string b = s.substr(i);
			if(a.front() != b.back() && b.front() != a.back())
				good = true;
		}
		if(good)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}