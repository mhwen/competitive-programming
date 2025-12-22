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
#define double long double

vector<double> diffs(vector<double> a) {
    vector<double> res(sz(a)-1);
    for(int i = 0; i < sz(a)-1; i++)
        res[i] = a[i+1]-a[i];
    return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	double k;
	cin >> n >> k;
	vector<double> a(n+2);
	for(int i = 1; i <= n; i++)
	    cin >> a[i];
	vector<double> p = diffs(diffs(a));
	stack<pair<double, int>> s;
	s.push({1e60, -1});
	double target = -2*k;
	double firstV = a[1];
	for(int i = 0; i < sz(p); i++) {
	    if(p[i] > target) {
	        while(p[i] > target) {
	            auto [amt, id] = s.top();
	            s.pop();
	            double x = p[i]-target;
	            int len = i-id;
	            double theirRatio = (double)1/(len+1);
	            if(amt/theirRatio > x || id == -1) {
	                amt -= x*theirRatio;
	                if(i+1 < sz(p))
	                    p[i+1] += x*(1-theirRatio);
	                s.push({amt, id});
	                p[i] = target;
	                if(id == -1)
	                    firstV += x*theirRatio;
	                else
	                    p[id] += x*theirRatio;
	            }
	            else {
	                double newX = amt/theirRatio;
	                p[i] -= newX;
	                if(i+1 < sz(p))
	                    p[i+1] += newX*(1-theirRatio);
	                p[id] = target;
	            }
	        }
	    }
	    else
	        s.push({target-p[i], i});
	}
	vector<double> res(n+1);
	res[0] = firstV;
	double delta = firstV;
	for(int i = 0; i < sz(p); i++) {
	    delta += p[i];
	    res[i+1] = res[i]+delta;
	}
	cout << fixed << setprecision(60);
	cout << *max_element(res.begin(), res.end()-1) << "\n";
}