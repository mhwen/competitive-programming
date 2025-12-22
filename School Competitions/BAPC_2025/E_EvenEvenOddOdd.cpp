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
	    vector<int> b(n);
	    for(int i = 0; i < n; i++)
	        cin >> a[i];
	    for(int i = 0; i < n; i++)   
	        cin >> b[i];
	    int bad = 0;
	    int odds = 0;
	    bool needEven = false;
	    for(int i = 0; i < n; i++) {
	        if(a[i]%2 != b[i]%2)
	            bad++;
	        else if(a[i] != b[i])
	            needEven = true;

	        if(a[i]%2==1)
	            odds++;
	    }
	    int evens = n-odds;
	    if(bad == 0) {
	        if(!needEven)
	            cout << "YES\n";
	        else if(evens%2==0)
	            cout << "YES\n";
	        else
	            cout << "NO\n";
	    }
	    else if(bad == 1 && odds%2==1)
	        cout << "YES\n";
	    else
	        cout << "NO\n";
	}
}