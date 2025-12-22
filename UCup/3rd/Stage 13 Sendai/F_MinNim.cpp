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
	    vector<int> a(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i];
	    int m = *min_element(all(a));
	    int cnt = 0;
	    for(int i : a)
	        if(i == m)
	            cnt++;
	    if(n%2==1 || cnt%2==1)
	        cout << "First\n";
	    else
	        cout << "Second\n";
	}
}