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
	    int n, m;
	    cin >> n >> m;
	    multiset<int> a;
	    for(int i = 0; i < n; i++) {
	        int num;
	        cin >> num;
	        a.insert(num);
	    }
	    
	    auto solve = [&](int num) {
	        int ones = 0;
	        map<int, int> cnts;
	        if(num == 1)
	            ones = 1;
	        else
	            cnts[num] = 1;
	        while(!cnts.empty()) {
	            map<int, int> newCnts;
	            for(auto [val, cnt] : cnts) {
	                while(cnt > 0 && a.count(val)) {
	                    cnt--;
	                    a.erase(a.find(val));
	                }
	                if(cnt) {
	                    int left = val/2;
	                    int right = (val+1)/2;
	                    if(left == 1)
	                        ones += cnt;
	                    else
	                        newCnts[left] += cnt;
	                    if(right == 1)
	                        ones += cnt;
	                    else
	                        newCnts[right] += cnt;
	                }
	            }
	            cnts = newCnts;
	        }
	        while(ones > 0 && a.count(1)) {
	            a.erase(a.find(1));
	            ones--;
	        }
	        return ones == 0;
	    };
	    
	    
	    vector<int> b(m);
	    for(int i = 0; i < m; i++) {
	        cin >> b[i];
	    }
	    bool bad = false;
	    for(auto num : b) {
	        if(!solve(num)) {
	            bad = true;
	            break;
	        }
	    }
	    if(bad || !a.empty())
	        cout << "NO\n";
	    else
	        cout << "YES\n";
	}
}