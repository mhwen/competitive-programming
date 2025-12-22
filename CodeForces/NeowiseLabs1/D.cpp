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
	    vector<int> x(n);
	    vector<int> y(n);
	    map<int, int> vert;
	    map<int, int> diag;
	    for(int i = 0; i < n; i++) {
	        cin >> x[i] >> y[i];
            vert[x[i]]++;
            diag[x[i]+y[i]]++;
	    }
	    int X = 0;
	    for(auto [xx, cnt] : vert) {
	        if(cnt%2==1) {
	            X = xx;
	            break;
	        }
	    }
	    for(auto [slope, cnt] : diag) {
	        if(cnt%2==1) {
	            int Y = slope-X;
	            cout << X << " " << Y << "\n";
	            break;
	        }
	    }
	}
}