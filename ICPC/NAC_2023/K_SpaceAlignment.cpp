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
	int n;
	cin >> n;
	int level = 0;
	vector<int> t;
	vector<int> a;
	vector<int> ks;
	for(int i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    int tabs = 0;
	    int spaces = 0;
	    if(s.back() == '}')
	        level--;
	    for(int j = 0; j < sz(s)-1; j++) {
	        if(s[j] == 't')
	            tabs++;
	        else
	            spaces++;
	    }
	    if(tabs+spaces > 0) {
	        if(level == 0) {
	            cout << -1 << "\n";
	            return 0;
	        }
	        t.pb(tabs);
	        a.pb(spaces);
	        ks.pb(level);
	    }
	    else if(level > 0) {
	        cout << -1 << "\n";
	        return 0;
	    }
	    if(s.back() == '{')
	        level++;
	}
	int ans = -1;
	for(int tab = 1; tab <= 1e3+5; tab++) {
	    if(t.empty()) {
	        ans = 1;
	        break;
	    }
    	if((t[0]*tab+a[0])%ks[0]!=0)
    	    continue;
    	int i = (t[0]*tab+a[0])/ks[0];
    	bool bad = false;
	    for(int j = 1; j < sz(t); j++) {
	        if(ks[j]*i != t[j]*tab+a[j]) {
	            bad = true;
	            break;
	        }
	    }
	    if(!bad) {
	        ans = tab;
	        break;
	    }
	}
	cout << ans << "\n";
}