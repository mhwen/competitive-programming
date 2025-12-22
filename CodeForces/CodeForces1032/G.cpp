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

typedef pair<ll, pair<ll, ll>> Info;

struct Node {
    vector<Info> pre, suf;
    ll zeros, ones;
};

constexpr ll INF = 1e9;

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
	    vector<int> one(n);
	    vector<int> zero(n);
	    for(int i = 0; i < n; i++) {
	        if(s[i]=='0')
	            zero[i]++;
	        else
	            one[i]++;
	    }
	    
	    auto combine = [](vector<Info>& L, vector<Info>& R, ll R0, ll R1) {
	        int li = 0, ri = 0;
	        vector<Info> res;
	        while(li < sz(L) && ri < sz(R)) {
	            Info newR = R[ri];
	            newR.first += R1-R0;
	            newR.second.first += R0;
	            newR.second.second += R1;
	            if(L[li].first < newR.first)
	                res.pb(L[li++]);
	            else {
	                res.pb(newR);
	                ri++;
	            }
	        }
	        while(li < sz(L))
	            res.pb(L[li++]);
	        while(ri < sz(R)) {
	            Info newR = R[ri];
	            newR.first += R1-R0;
	            newR.second.first += R0;
	            newR.second.second += R1;
	            res.pb(newR);
	            ri++;
	        }
	        return res;
	    };
	    
	    
	    ll ans = 0;
	    auto merge = [&](Node& left, Node& right) {
	          for(Info suf : left.suf) {
	              // count how many pre > -suf
	              ll need = -suf.first;
	              auto it = upper_bound(all(right.pre), pair{need, pair{INF, INF}});
	              int over = (int)(right.pre.end()-it);
	              int under = sz(right.pre)-over;
	              ans += suf.second.second*over + suf.second.first*under;
	          }
	          for(Info pre : right.pre) {
	              // count how many suf > -pre
	              ll need = -pre.first;
	              auto it = upper_bound(all(left.suf), pair{need, pair{INF, INF}});
	              int over = (int)(left.suf.end()-it);
	              int under = sz(left.suf)-over;
	              ans += pre.second.second*over + pre.second.first*under;
	          }
	          Node res;
	          res.pre = combine(left.pre, right.pre, left.zeros, left.ones);
	          res.suf = combine(right.suf, left.suf, right.zeros, right.ones);
	          res.ones = left.ones+right.ones;
	          res.zeros = left.zeros+right.zeros;
	          return res;
	          
	    };
	    function<Node(int, int)> solve = [&](int l, int r) {
	        if(l == r) {
	            ans++;
	            Info I = {one[l]-zero[l], {zero[l], one[l]}};
	            Node node;
	            node.pre.pb(I);
	            node.suf.pb(I);
	            node.zeros = zero[l];
	            node.ones = one[l];
	            return node;
	        }
	        int m = (l+r)/2;
	        Node left = solve(l, m);
	        Node right = solve(m+1, r);
	        return merge(left, right);
	    };
	    solve(0, n-1);
	    cout << ans << "\n";
	}
	
}