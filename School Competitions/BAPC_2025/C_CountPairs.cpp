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
	vector<int> good(1<<20, -1);
	for(int i = 0; i < n; i++) {
	    int num;
	    cin >> num;
	    int v = -1;
	    for(int bit = 0; bit < 20; bit++) {
	        if(num & (1<<bit))
	            v = bit;
	    }
	    good[num] = v;
	}
	for(int mask = 0; mask < sz(good); mask++) {
	    for(int bit = 0; bit < 20; bit++) {
	        if(mask & (1<<bit)) {
	            int prev = mask^(1<<bit);
	            good[mask] = max(good[mask], good[prev]);
	        }
	    }
	}
	vector<int> dp(1<<20, 0);
	for(int mask = 0; mask < sz(dp); mask++) {
	    int v = -1;
	    for(int bit = 0; bit < 20; bit++) {
	        if(mask & (1<<bit))
	            v = bit;
	    }
	    for(int next = v+1; next < 20; next++) {
	        int tot = (1<<(next+1))-1;
	        int free = tot^mask;
	        int newMask = mask|(1<<next);
	        if(good[free] == next)
	            dp[newMask] = max(dp[newMask], dp[mask]+1);
	    }
	}
	cout << *max_element(all(dp)) << "\n";
}