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
	    cin >> n;
	    map<int, int> freq;
	    for(int i = 0; i < n; i++) {
	        int a;
	        cin >> a;
	        freq[a]++;
	    }
	    int twice = -1;
	    vector<int> extra;
	    for(auto [v, cnt] : freq) {
	        if(cnt >= 4) {
	            cout << v << " " << v << " " << v << " " << v << "\n";
	            goto done;
	        }
	        else if(cnt >= 2) {
	            if(twice != -1) {
	                cout << twice << " " << twice << " " << v << " " << v << "\n";
	                goto done;
	            }
	            else {
	                twice = v;
	                if(cnt == 3)
	                    extra.push_back(v);
	            }
	        }
	        else
	            extra.push_back(v);
	    }
	    if(twice == -1) {
	        cout << -1 << "\n";
	    }
	    else {
	        bool found = false;
	        for(int i = 0; i < sz(extra)-1; i++) {
	            int diff = extra[i+1]-extra[i];
	            if(diff < 2*twice) {
	                found = true;
	                cout << twice << " " << twice << " " << extra[i+1] << " " << extra[i] << "\n";
	                break;
	            }
	        }
	        if(!found)
	            cout << -1 << "\n";
	    }   
	    done:
	    {}
	}
}