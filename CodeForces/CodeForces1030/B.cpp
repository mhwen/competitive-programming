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
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    cout << 2*n-1 << "\n";
	    cout << 1 << " " << 1 << " " << n << "\n";
	    for(int i = 2; i <= n; i++) {
	        cout << i << " " << 1 << " " << n-i+1 << "\n";
	        cout << i << " " << n-i+2 << " " << n << "\n";
	    }
	}
}