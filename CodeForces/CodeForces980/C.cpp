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

vector<int> z_function(vector<int>& A, vector<int>& B) {
    int n = sz(A)+2*sz(B);
    auto s = [&](int i) {
        if(i < sz(A))
            return A[i];
        i -= sz(A);
        if(i >= sz(B))
            i -= sz(B);
        return B[i];
    };
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s(z[i]) == s(i + z[i])) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

pair<int, pair<vector<int>, vector<int>>> getGraph(int n, int k) {
    vector<int> inOut(n);
    for(int i = 0; i < n; i++)
        cin >> inOut[i];
    int deg = accumulate(all(inOut), 0);
    vector<vector<int>> con(n);
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].pb(b);
    }
    vector<int> inParity(k);
    vector<int> outParity(k);
    vector<int> vis(n, -1);
    auto dfs = [&](auto&& self, int curr, int p) {
        if(vis[curr] != -1) {
            assert(p == vis[curr]);
            return;
        }
        vis[curr] = p;
        if(inOut[curr] == 0)
            inParity[p]++;
        else
            outParity[p]++;
        for(int next : con[curr]) {
            self(self, next, (p+1)%k);
        }
    };
    dfs(dfs, 0, 0);
    return pair{deg, pair{inParity, outParity}};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
    	int n, k;
    	cin >> n >> k;
    	auto [Adeg, Ainfo] = getGraph(n, k);
    	auto& [Ain, Aout] = Ainfo;
    	auto [Bdeg, Binfo] = getGraph(n, k);
    	auto& [Bin, Bout] = Binfo;
    	if(Adeg != n-Bdeg) {
    	    cout << "NO\n";
    	    continue;
    	}
    	if(Adeg == 0 || Bdeg == 0) {
    	    cout << "YES\n";
    	    continue;
    	}
    	
    	auto check = [&](vector<int>& A, vector<int>& B) {
    	    vector<int> good(k);
    	    vector<int> z = z_function(A, B);
    	    for(int shift = 0; shift < k; shift++) {
    	        if(z[shift+k] >= k)
    	            good[shift]++;
    	    }
    	    return good;
    	};
    	auto g1 = check(Aout, Bin);
    	auto g2 = check(Bout, Ain);
    	bool good = false;
    	for(int i = 0; i < k; i++) {
    	    int j = (k+2-i)%k;
    	    if(g1[i] && g2[j])
    	        good = true;
    	}
    	if(good)
    	    cout << "YES\n";
    	else
    	    cout << "NO\n";
    }
}