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
	    string s;
	    cin >> n >> s;
        int cnt = 0;
        vector<ll> dists;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'B') {
                if(i-cnt > 0)
                    dists.push_back(i-cnt);
                cnt++;
            }
        }
        ll ans = 0;
        stack<ll> rem;
        for(auto d : dists) {
            if(rem.empty() || rem.top()%2 != d%2)
                rem.push(d);
            else {
                ans += (rem.top()+d)/2;
                rem.pop();
            }
        }
        while(!rem.empty()) {
            ans += (rem.top()+1)/2;
            rem.pop();
        }
        cout << ans << "\n";
    }
}