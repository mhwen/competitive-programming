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
	int n;
	cin >> n;
	vector<string> s(n);
	for(int i = 0; i < n; i++)
	    cin >> s[i];
	sort(all(s), [](string a, string b) {
	   return sz(a) < sz(b); 
	});
	string ans = s[0];
	for(int i = 1; i < n; i++) {
	    if(!s[i].ends_with(s[0]))
	        ans = "Not found";
	}
	cout << ans << "\n";
}