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
	int n, d;
	cin >> n >> d;
	vector<int> l(n);
	vector<int> w(n);
	vector<int> h(n);
	for(int i = 0; i < n; i++)
	    cin >> l[i] >> w[i] >> h[i];
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int i, int j) {
	    return w[i] > w[j];
	});
	stack<pair<int, ll>> s;
	s.push({1e9, 0});
	
	auto add = [&](pair<int, ll> v) {
	    // cout << "adding " << v.first << " " << v.second << endl;
	    // cout << s.top().first << " " << s.top().second << endl;
	    assert(s.top().first > v.first);
	    if(v.second > s.top().second)
	        s.push(v);
	};
	
	int ans = 0;
	for(int me : order) {
	    // cout << "Me: " << me+1 << endl;
	    stack<pair<int, ll>> old;
	    while(s.top().first < w[me]) {
	        old.push(s.top());
	        s.pop();
	    }
	    // cout << s.top().first << " " << s.top().second << endl;
	    if(s.top().second+l[me] > d)
	        ans++;
	    
	    stack<pair<int, ll>> newPiles;
	    stack<pair<int, ll>> hold;
	    while(s.top().first < w[me]*2) {
	        newPiles.push({s.top().first-w[me], s.top().second+h[me]});
	        hold.push(s.top());
	        s.pop();
	    }

	    if(newPiles.empty() || newPiles.top().first < w[me]-1)
	        newPiles.push({w[me]-1, h[me]+s.top().second});
	    
	    while(!hold.empty()) {
	        s.push(hold.top());
	        hold.pop();
	    }
	    while(!old.empty() && !newPiles.empty()) {
	        auto a = old.top();
	        auto b = newPiles.top();
	        if(a.first > b.first) {
	            add(a);
	            old.pop();
	        }
	        else if(b.first > a.first) {
	            add(b);
	            newPiles.pop();
	        }
	        else {
	            if(a.second < b.second)
	                swap(a, b);
	            add(a);
	            newPiles.pop();
	            old.pop();
	        }
	    }
	    while(!old.empty()) {
	        add(old.top());
	        old.pop();
	    }
	    while(!newPiles.empty()) {
	        add(newPiles.top());
	        newPiles.pop();
	    }
	}
	cout << ans << "\n";
}