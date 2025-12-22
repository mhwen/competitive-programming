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
	    int a, b, c, d, e, f;
	    cin >> e >> f >> c >> d >> a >> b;
	    auto make = [&](int X, int Y) {
	        if(a == c && a == X && b+d==Y)
	            return "YES\n";
	        else if(b == d && b == Y && a+c==X)
	            return "YES\n";
	        else
	            return "NO\n";
	    };
	    if(e >= f)
	        cout << make(e, e-f);
	    else
	        cout << make(f-e, f);
	}
}