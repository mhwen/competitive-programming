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

typedef pair<pair<int, int>, pair<int, int>> I;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++)
	    cin >> a[i];
	vector<int> kill(n+1);
	queue<I> waiting;
	int curr = 0;
	set<pair<int, int>> seen;
	for(int i = 0; i < n-1; i++) {
	    int mn = a[i];
	    int mx = a[i+1];
	    if(mn > mx)
	        swap(mn, mx);
	    waiting.push({{i, i+1}, {mn, mx}});
	}
	bool bad = false;
	for(int k = n; k >= 1; k--) {
	    while(curr < k && !waiting.empty()) {
	        I next = waiting.front();
	        waiting.pop();
	        auto [interval, mnmx] = next;
	        auto [l, r] = interval;
	        auto [mn, mx] = mnmx;
	        if(mx-mn > k)
	            continue;
	        curr++;
	        kill[mx-mn]++;
	        
	        if(l-1 >= 0 && !seen.count({l-1, r})) {
	            waiting.push({{l-1, r}, {min(mn, a[l-1]), max(mx, a[l-1])}});
	            seen.insert({l-1, r});
	        }
	        if(r+1 < n && !seen.count({l, r+1})) {
	            waiting.push({{l, r+1}, {min(mn, a[r+1]), max(mx, a[r+1])}});
	            seen.insert({l, r+1});
	        }
	    }
	    if(curr < k) {
	        bad = true;
	        break;
	    }
	    curr -= kill[k];
	}
	if(bad)
	    cout << "unstable\n";
	else
	    cout << "stable\n";
}