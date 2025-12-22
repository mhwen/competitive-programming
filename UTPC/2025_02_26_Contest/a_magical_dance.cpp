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
	string s;
	cin >> s;
	auto isEW = [&](char c) {
	    return c == 'E' || c == 'W';
	};
	int a1 = 0, a2 = 0;
	for(int i = 0; i < n; i++) {
	    if(i%2==0) {
    	    if(isEW(s[i]))
    	        a1++;
    	    else
    	        a2++;
	    }
	    else {
	        if(isEW(s[i]))
    	        a2++;
    	    else
    	        a1++;
	    }
	}
	cout << max(a1, a2) << "\n";
	
}