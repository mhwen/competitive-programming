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
	string ans = "makes sense";
	for(int i = 0; i < n; i++) {
	    string s;
	    cin >> s;
	    if(s != "mumble") {
	        if(stoi(s) != i+1)
	            ans = "something is fishy";
	    }
	}
	cout << ans << "\n";
}