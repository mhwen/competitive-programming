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
	int n, m, vk, hk;
	cin >> n >> m >> vk >> hk;
	vector<string> grid(n);
	for(int i = 0; i < n; i++)
	    cin >> grid[i];
	auto id = [&](int r, int c) {
	    return r*m+c;
	};
	int q;
	cin >> q;
	vector<pair<int, int>> queries(q);
	for(int i = 0; i < q; i++) {
	    int r, c;
	    cin >> r >> c;
	    r--; c--;
	    grid[r][c] = '@';
	    queries[i] = {r, c};
	}
	vector<int> p(n*m);
	vector<int> even(n*m);
	vector<int> odd(n*m);
	vector<set<int>> rows(n);
	vector<set<int>> cols(m);
	iota(all(p), 0);
	for(int r = 0; r < n; r++) {
	    rows[r].insert(-1);
	    rows[r].insert(m);
	}
	for(int c = 0; c < m; c++) {
	    cols[c].insert(-1);
	    cols[c].insert(n);
	}
	for(int r = 0; r < n; r++) {
	    for(int c = 0; c < m; c++) {
	        int R = r/vk;
	        int C = c/hk;
	        if((R+C)%2==0)
	            even[id(r,c)]++;
	        else
	            odd[id(r,c)]++;
	        if(grid[r][c] == '@') {
	            rows[r].insert(c);
	            cols[c].insert(r);
	        }
	    }
	}
	
	function<int(int)> getPar = [&](int a) -> int {
	    if(a == p[a])
	        return a;
	    return p[a] = getPar(p[a]);
	};
	auto merge = [&](int a, int b) {
	    a = getPar(a);
	    b = getPar(b);
	    if(a == b)
	        return 0LL;
	    if(even[a]+odd[a] > even[b]+odd[b])
	        swap(a, b);
	    ll extra = (ll)even[a]*even[b]+(ll)odd[a]*odd[b];
	    p[a] = b;
	    even[b] += even[a];
	    odd[b] += odd[a];
	    return extra*2;
	};
	
	ll curr = 0;
	for(int r = 0; r < n; r++) {
	    for(int c = 0; c+hk < m; c++) {
	        auto it = rows[r].lower_bound(c);
	        assert(it != rows[r].end());
	        if(*it-c > hk)
	            curr += merge(id(r,c), id(r,c+hk));
	    }
	}
	for(int c = 0; c < m; c++) {
	    for(int r = 0; r+vk < n; r++) {
	        auto it = cols[c].lower_bound(r);
	        assert(it != cols[c].end());
	        if(*it-r > vk)
	            curr += merge(id(r,c), id(r+vk,c));
	    }
	}
	
	vector<ll> ans(q+1);
	ans[q] = curr;
	for(int i = q-1; i >= 0; i--) {
	    auto [r,c] = queries[i];
	    rows[r].erase(c);
	    auto hiC = rows[r].lower_bound(c);
	    auto loC = prev(hiC);
	    for(int C = max(*loC+1, c-hk); C+hk <= min(*hiC-1, c+hk); C++)
	        curr += merge(id(r,C), id(r,C+hk));
	    cols[c].erase(r);
	    auto hiR = cols[c].lower_bound(r);
	    auto loR = prev(hiR);
	    for(int R = max(*loR+1, r-vk); R+vk <= min(*hiR-1, r+vk); R++)
	        curr += merge(id(R,c), id(R+vk,c));
	    ans[i] = curr;
	}
	for(auto a : ans)
	    cout << a << " ";
	cout << "\n";
    
}