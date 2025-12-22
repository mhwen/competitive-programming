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
	
	auto print = [&](int i) {
	    for(int bit = n-1; bit >= 0; bit--) {
	        if(i&(1<<bit))
	            cout << 1;
	        else
	            cout << 0;
	    }
	    cout << "\n";
	};
	vector<bool> used(1<<n);
	vector<int> ans;
	
	for(int i = 0; i < (1<<n); i++) {
	    if(used[i])
	        continue;
	    used[i] = true;
	    ans.push_back(i);
	    for(int bit = 0; bit < n; bit++)
	        used[i|(1<<bit)] = true;
	}
	cout << sz(ans) << "\n";
	for(auto num : ans)
	    print(num);
}