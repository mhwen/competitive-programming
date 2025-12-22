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

vector<int> query(vector<int> v) {
    cout << "? " << sz(v);
    for(int a : v)
        cout << " " << a+1;
    cout << endl;
    int c;
    cin >> c;
    vector<int> res(c);
    for(int i = 0; i < c; i++) {
        cin >> res[i];
        res[i]--;
    }
    return res;
}

void answer(vector<int> v) {
    // sort(all(v));
    cout << "!";
    for(int a : v)
        cout << " " << a+1;
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t-->0) {
        int n;
        cin >> n;
        vector<int> p(n*n+1);
        iota(all(p), 0);
        vector<vector<int>> con1(n*n+1);
        vector<vector<int>> con2(n*n+1);
        vector<int> d1(n*n+1);
        vector<int> d2(n*n+1);
        for(int its = 0; its < n && !p.empty(); its++) {
            vector<int> res = query(p);
            set<int> has(all(res));
            vector<int> newP;
            for(int i = 0; i < sz(p); i++) {
                if(has.count(p[i])) {
                    for(int j = 0; j < i; j++) {
                        con1[p[i]].pb(p[j]);
                        d1[p[j]]++;
                    }
                    for(int j = i+1; j < sz(p); j++) {
                        if(has.count(p[j]))
                            break;
                        con2[p[j]].pb(p[i]);
                        d2[p[i]]++;
                    }
                }
                else
                    newP.pb(p[i]);
            }
            swap(p, newP);
        }
        auto go = [&](vector<vector<int>>& con, vector<int>& d) {
            queue<int> q;
            vector<int> prev(n*n+1, -1), len(n*n+1, 1);
            for(int i = 0; i < n*n+1; i++) {
                if(d[i] == 0)
                    q.push(i);
            }
            while(!q.empty()) {
                int curr = q.front();
                q.pop();
                for(int next : con[curr]) {
                    if(len[next] < len[curr]+1) {
                        len[next] = len[curr]+1;
                        prev[next] = curr;
                    }
                    d[next]--;
                    if(d[next] == 0)
                        q.push(next);
                }
            }
            vector<int> res;
            for(int i = 0; i < n*n+1; i++) {
                if(len[i] == n+1) {
                    int curr = i;
                    res.pb(curr);
                    for(int j = 0; j < n; j++) {
                        curr = prev[curr];
                        res.pb(curr);
                    }
                    answer(res);
                    return true;
                }
            }
            return false;
        };
        
        bool success = go(con1, d1);
        if(!success)
            success = go(con2, d2);
        assert(success);
    }
}