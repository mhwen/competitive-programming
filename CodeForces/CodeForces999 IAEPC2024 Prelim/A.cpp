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
	    int evens = 0, odds = 0;
	    for(int i = 0; i < n; i++) {
	        int a;
	        cin >> a;
	        if(a%2==0)
	            evens++;
	        else
	            odds++;
	    }
	    if(evens)
	        cout << 1+odds << "\n";
	    else
	        cout << odds-1 << "\n";
	}
}