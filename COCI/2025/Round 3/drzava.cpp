#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

constexpr ll MOD = 1e9+7;

void print(vector<ll>& a) {
    for(ll v : a)
        cout << v << " ";
    cout << endl;
}

vector<ll> merge(vector<ll>& a, vector<ll>& b) {
    vector<ll> res(sz(a)+sz(b)-1);
    for(int len = 0; len < sz(res); len++) {
        for(int A = 0; A < sz(a); A++) {
            int B = len-A;
            if(B >= sz(b) || B < 0)
                continue;
            res[len] += a[A]*b[B]%MOD;
            res[len] %= MOD;
        }
    }
    return res;
}

vector<ll> recover(vector<ll>& a, vector<ll>& res) {
    vector<ll> b(sz(res)-sz(a)+1);
    vector<ll> delta(sz(b));
    for(int i = 0; i < sz(b); i++) {
        b[i] = res[i]+delta[i];
        for(int j = 0; i+j < sz(res); j++) {
            if(j >= sz(a) || i+j >= sz(b))
                break;
            delta[i+j] -= a[j]*b[i]%MOD;
            delta[i+j] += MOD;
            delta[i+j] %= MOD;
        }
    }
    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> con(n);
    for(int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        con[a].push_back(b);
        con[b].push_back(a);
    }
    
    vector<vector<ll>> ways(n);
    auto mergeChildren = [&](int curr, int prev, vector<ll> start) {
        priority_queue<pair<int, int>> q;
        vector<vector<ll>> children;
        children.push_back(start);
        q.push({-sz(start), 0});
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            children.push_back(ways[next]);
            q.push({-sz(ways[next]), sz(children)-1});
        }
        while(sz(q) > 1) {
            auto [_, id1] = q.top();
            q.pop();
            auto [__, id2] = q.top();
            q.pop();
            children[id1] = merge(children[id1], children[id2]);
            q.push({-sz(children[id1]), id1});
        }
        auto [_, id] = q.top();
        return children[id];
    };
    
    function<void(int, int)> dfs = [&](int curr, int prev) {
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            dfs(next, curr);
        }
        vector<ll> res = mergeChildren(curr, prev, vector<ll>{1});
        if(sz(res) == 1)
            res.push_back(0);
        res[1]++;
        res[1] %= MOD;
        ways[curr] = res;
    };
    dfs(0, -1);
    
    vector<ll> ans(n+1);
    function<void(int, int, vector<ll>)> reroot = [&](int curr, int prev, vector<ll> pWays) {
        vector<ll> myWays = mergeChildren(curr, prev, pWays);
        for(int i = 0; i < sz(myWays); i++) {
            ans[i+1] += myWays[i];
            ans[i+1] %= MOD;
        }
        for(int next : con[curr]) {
            if(next == prev)
                continue;
            vector<ll> newP = recover(ways[next], myWays);
            if(sz(newP) == 1)
                newP.push_back(0);
            newP[1]++;
            newP[1] %= MOD;
            reroot(next, curr, newP);
        }
    };
    reroot(0, -1, vector<ll>{1});
    
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}