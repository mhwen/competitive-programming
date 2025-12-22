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
	    vector<int> ans(n);
	    ans[0] = 1;
	    int mn = 0, mx = 2;
	    for(int i = 1; i < n; i++) {
	        if(s[i-1] == '<')
	            ans[i] = mn--;
	        else
	            ans[i] = mx++;
	    }
	    int lo = *min_element(all(ans));
	    for(int a : ans)
	        cout << a+1-lo << " ";
	    cout << "\n";
	}
	
}