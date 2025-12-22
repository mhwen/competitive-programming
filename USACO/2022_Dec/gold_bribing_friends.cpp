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
	int n, A, B;
	cin >> n >> A >> B;
	vector<int> p(n), c(n), x(n);
	for(int i = 0; i < n; i++)
	    cin >> p[i] >> c[i] >> x[i];
	vector<int> order(n);
	iota(all(order), 0);
	sort(all(order), [&](int i, int j) {
	    return x[i] < x[j];
	});
	vector<int> free(B+1);
	vector<int> dp(A+1);
	for(int o : order) {
	    int P = p[o];
	    int C = c[o];
	    int X = x[o];
	    for(int i = sz(dp)-1; i >= 0; i--) {
	        if(i+C >= sz(dp))
	            continue;
	        dp[i+C] = max(dp[i+C], dp[i]+P);
	    }
	    for(int i = sz(free)-1; i >= 0; i--) {
	        int rem = B-i;
	        int take = min(C, rem/X);
	        int newC = C-take;
	        if(newC) {
	            if(newC <= A)
	                dp[newC] = max(dp[newC], free[i]+P);
	        }
	        else
	            free[i+take*X] = max(free[i+take*X], free[i]+P);
	    }
	}
	cout << max(*max_element(all(free)), *max_element(all(dp))) << "\n";
}