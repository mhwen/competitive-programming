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
#define double long double
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define pb push_back

typedef vector<double> poly;
typedef pair<pair<int, int>, int> state;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k;
	cin >> n >> k;
	
	vector<double> X(k+2);
	for(int i = 1; i < sz(X); i++) {
	    X[i] = pow((double)1/k, i)/i;
	}
	
	auto outside = [&](int bit, int mask) {
	    return bit < k && !(mask&(1<<bit));
	};
	auto beatable = [&](int a, int b) {
	    return a+k > b;
	};
	auto beatableInOne = [&](int a, int b) {
	    return a >= b;
	};

	auto multiply = [&](poly a, poly b) {
	    poly res(sz(a)+sz(b)-1);
	    for(int i = 0; i < sz(a); i++) {
	        for(int j = 0; j < sz(b); j++) {
	            res[i+j] += a[i]*b[j];
	        }
	    }
	    return res;
	};
	
	vector dp(k+1, vector((1<<k), vector<double>(k+1)));

	for(int gap = 0; gap < k+1; gap++) {
	    for(int mask = 1; mask < (1<<k); mask++) {
	        for(int two = 0; two < k+1; two++) {
	            if(outside(two, mask))
	                continue;
	            int myLo = two + (two == k ? gap : 0);
	            for(int one = 0; one < k+1; one++) {
	                if(outside(one, mask) || one == two)
	                    continue;
	                int oneLo = one + (one == k ? gap : 0);
    	            for(int step = 0; step < k; step++) {
    	                if(!beatable(oneLo, myLo+step))
    	                    break;
    	                poly p{1};
    	                if(beatableInOne(myLo+step, oneLo))
    	                    p = {(oneLo+k-(myLo+step))*X[1], -1};
    	                bool good = true;
    	                for(int them = k; them >= 0; them--) {
    	                    if(outside(them, mask) || them == one || them == two)
    	                        continue;
    	                    int theirLo = them + (them == k ? gap : 0);
    	                    if(!beatableInOne(myLo+step, theirLo)) {
    	                        good = false;
    	                        break;
    	                    }
    	                    if(beatable(theirLo, myLo+step)) {
    	                        poly q{1};
    	                        q = {(myLo+step-theirLo)*X[1], 1};
    	                        p = multiply(p, q);
    	                    }
    	                }
    	                //it is possible, let's integrate
    	                if(good) {
    	                    double res = 0;
    	                    for(int i = 0; i < sz(p); i++)
    	                        res += X[i+1]*p[i];
    	                    dp[gap][mask][two] += res;
    	                }
    	            }
	            }
	        }
	    }
	}
	map<state, double> curr;
	int m = 0;
	for(int bit = 0; bit < k; bit++) {
	    m *= 2;
	    if(bit < n-1)
	        m++;
	}
	curr[{{m, 0}, n-1-k}] = 1.0;
	vector<double> ans(n);
	for(int rem = n; rem > 1; rem--) {
	    map<state, double> next;
	    for(auto [info, prob] : curr) {
	        auto [mg, ID] = info;
	        auto [mask, gap] = mg;
	        int seen = __builtin_popcount(mask)+1;
	        for(int two = 0; two < k+1; two++) {
	            int idOffset = ID;
	            int extra = rem-seen;
	            if(dp[gap][mask][two] == 0)
	                continue;
	            // probability two gets out 
	            double P = dp[gap][mask][two]*prob;
	            int player = idOffset+two + (two == k ? gap : 0);
                int newMask = (two == k) ? (mask^(1<<(k-1))) : (mask^(1<<two));
                int newGap = (two == k) ? -1 : gap;
                if(rem > 2) {
                    while(!(newMask&(1<<(k-1)))) {
                        newMask <<= 1;
                        newGap++;
                        if(extra) {
                            extra--;
                            newMask++;
                        }
                        idOffset--;
                    }
                }
                int topPlayer = idOffset+k+newGap;
                //top player becomes guaranteed #1
                if(gap < k && (newGap >= k || rem == 2))
                    ans[topPlayer] += P;
                newGap = min(newGap, k);
                ans[player] += P*rem;
                next[{{newMask, newGap}, idOffset}] += P;
	        }
	    }
	    curr = next;
	}
	cout << fixed << setprecision(20);
	for(auto a : ans)
	    cout << a << "\n";
}