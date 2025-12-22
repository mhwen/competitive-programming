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
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i];
	    int G = 0;
	    for(int i = 0; i < n; i++)
	        G = gcd(G, a[i]);
	    int more = 0;
	    for(int i = 0; i < n; i++)
	        if(a[i] != G)
	            more++;
	    vector<int> moves(5001, 1e6);
	    moves[G] = 0;
	    for(int v = G+G; v <= 5000; v+=G) {
	        int ans = 1e6;
	        for(auto num : a) {
	            ans = min(ans, moves[gcd(v, num)]+1);
	        }
	        moves[v] = ans;
	    }
	    int ans = 1e6;
	    for(int i = 0; i < n; i++) {
	        int need = more;
	        if(a[i] != G)
	            need--;
	        ans = min(ans, moves[a[i]]+need);
	    }
	    cout << ans << "\n";
	}
}