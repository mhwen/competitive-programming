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
	    vector<int> h(n);
	    for(int i = 0; i < n; i++)
	        cin >> h[i];
	    vector<int> pre(n);
	    for(int i = 1; i < n; i++) {
	        if(h[i] < h[i-1])
	            pre[i]++;
	        pre[i] += pre[i-1];
	    }
	    vector<int> suf(n);
	    for(int i = n-2; i >= 0; i--) {
	        if(h[i] < h[i+1])
	            suf[i]++;
	        suf[i] += suf[i+1];
	    }
	    for(int i = 0; i < n; i++)
	        cout << max(pre[i], suf[i]) << " ";
	    cout << "\n";
	}
}