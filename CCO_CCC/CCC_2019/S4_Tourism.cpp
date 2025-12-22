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
	int n, k;
	cin >> n >> k;
	vector<ll> A(n);
	for(int i = 0; i < n; i++)
	    cin >> A[i];
	int x = (k-n%k)%k;
	//from i*k-x to i*k
	vector<ll> dp(n);
	for(int i = 0; i < k; i++) {
	    dp[i] = A[i];
	    if(i > 0)
	        dp[i] = max(dp[i], dp[i-1]);
	}

	vector<priority_queue<pair<ll, int>>> group(n);
	vector<bool> dead(n);
	multiset<ll> bests;
	vector<ll> mx(n);
	
	vector<int> p(n);
	iota(all(p), 0);
	function<int(int)> getPar = [&](int a) {
	    if(a == p[a])
	        return a;
	    return p[a] = getPar(p[a]);
	};
	
	auto remove = [&](int a) {
	    a = getPar(a);
	    if(!group[a].empty())
	        bests.erase(bests.find(group[a].top().first+mx[a]));
	};
	auto add = [&](int a) {
	    a = getPar(a);
	    if(!group[a].empty())
	        bests.insert(group[a].top().first+mx[a]);
	};
	auto upd = [&](int a) {
	    a = getPar(a);
	    if(!group[a].empty() && dead[group[a].top().second]) {
	        remove(a);
	        while(!group[a].empty() && dead[group[a].top().second])
	            group[a].pop();
	        add(a);
	    }
	};

	auto merge = [&](int a, int b) {
	    a = getPar(a);
	    b = getPar(b);
	    if(a == b)
	        return;
	    if(sz(group[a]) < sz(group[b]))
	        swap(a, b);
	    remove(a);
	    remove(b);
	    
	    while(!group[b].empty()) {
	        group[a].push(group[b].top());
	        group[b].pop();
	    }

	    mx[a] = max(mx[a], mx[b]);
	    p[b] = a;
	    add(a);
	};
	auto kill = [&](int a) {
	    dead[a] = true;
	    upd(a+1);
	};

	for(int block = 1; block < (n+k-1)/k; block++) {
	    bests.clear();
	    stack<int> s;
	    for(int i = block*k-x; i < min(n, (block+1)*k); i++) {
	        p[i] = i;
	        while(!group[i].empty())
	            group[i].pop();
	        mx[i] = A[i];
	        dead[i] = false;
	        if(i <= block*k) {
	            group[i].push({dp[i-1], i-1});
	            add(i);
	        }
	        while(!s.empty() && mx[getPar(s.top())] <= mx[getPar(i)]) {
	            merge(s.top(), i);
	            s.pop();
	        }
	        s.push(i);
	        if(i-k-1 >= block*k-x-1)
	            kill(i-k-1);
	        assert(!bests.empty());
	        if(i >= block*k) {
	            dp[i] = *bests.rbegin();
	        }
	    }
	}
	cout << dp.back() << "\n";
}