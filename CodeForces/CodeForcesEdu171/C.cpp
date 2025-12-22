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
		ll tot = (ll)n*(n+1)/2;
		string s;
		cin >> s;
		int used = 0;
		for(int i = n-1; i >= 0; i--) {
			if(s[i] == '1' && used+1<=i) {
				used++;
				tot -= i+1;
			}
			else if(used > 0)
				used--;
		}
		cout << tot << "\n";
	}
}