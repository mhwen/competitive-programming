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
	vector<int> add(365);
	for(int i = 0; i < n; i++) {
	    int d;
	    cin >> d;
	    d--;
	    add[d]++;
	}
	int curr = 0;
	int dirt = 0;
	int ans = 0;
	for(int i = 0; i < sz(add); i++) {
        curr += add[i];
	    if(dirt+curr >= 20) {
	        dirt = 0;
	        curr = 0;
	        ans++;
	    }
	    else
	        dirt += curr;
	}
	if(dirt+curr > 0)
	    ans++;
	cout << ans << "\n";
}