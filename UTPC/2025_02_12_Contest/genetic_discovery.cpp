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
	int n;
	cin >> n;
	string ans;
	cin >> ans;
	vector<bool> bad(sz(ans));
	for(int i = 0; i < n-1; i++) {
	    string s;
	    cin >> s;
	    for(int j = 0; j < sz(s); j++) {
	        if(ans[j] == '.')
	            ans[j] = s[j];
	        else if(s[j] != '.' && s[j] != ans[j])
    	        bad[j] = true;
	    }
	}
	for(int i = 0; i < sz(ans); i++) {
	    if(bad[i])
	        cout << '.';
	    else
	        cout << ans[i];
	}
	cout << "\n";
}