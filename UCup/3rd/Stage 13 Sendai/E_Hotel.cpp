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
	int q;
	cin >> q;
	vector<int> type(1);
	vector<vector<int>> v(1);
	type.back() = 1;
	v.back().push_back(1);
	ll n = 1;
	while(q-->0) {
	    int t, x;
	    cin >> t >> x;
	    if(t == 1) {
	        v.back().push_back(x);
	        n++;
	    }
	    else if(t == 2) {
	        type.push_back(2);
	        v.push_back(vector<int>{x});
	        type.push_back(1);
	        v.push_back(vector<int>{});
	        n *= 2;
	        n = min(n, (ll)1e9+5);
	    }
	    else {
	        x--;
	        if(x >= n)
	            cout << -1 << "\n";
	        else {
	            for(int i = sz(v)-1; i >= 0; i--) {
	                auto &nums = v[i];
	                if(type[i] == 1) {
	                    if(x < sz(nums)) {
	                        cout << nums[sz(nums)-1-x] << "\n";
	                        break;
	                    }
	                    else
	                        x -= sz(nums);
	                }
	                else {
	                    if(x%2==0) {
	                        cout << nums[0] << "\n";
	                        break;
	                    }
	                    else {
	                        x /= 2;
	                    }
	                }
	            }
	        }
	    }
	}
}