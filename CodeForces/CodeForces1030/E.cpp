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

int nextL(int i) {
    if(i == 0)
        return 1;
    else if(i < 0)
        return -i+1;
    else
        return -i;
}
int nextR(int i) {
    if(i == 0)
        return -1;
    else if(i < 0)
        return -i;
    else
        return -i-1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	
	while(t-->0) {
	    int n, m;
	    cin >> n >> m;
	    int cy = (n+1)/2;
	    int cx = (m+1)/2;
	    cout << cy << " " << cx << "\n";
	    for(int i = 1; i < (max(n, m)+1)/2; i++) {
	        //top bot
	        if(cy+i <= n) {
	            int lo = 0;
	            int hi = 0;
	            for(int j = 0; j < 2*i-1; j++) {
	                if(cx+lo > m || cx+hi > m)
	                    break;
	                cout << cy+i << " " << cx+lo << "\n";
	                cout << cy-i << " " << cx+hi << "\n";
	                lo = nextL(lo);
	                hi = nextR(hi);
	            }
	        }
	        //left right
	        if(cx+i <= m) {
	            int left = 0;
	            int right = 0;
	            for(int j = 0; j < 2*i-1; j++) {
	                if(cy+left > n || cy+right > n)
	                    break;
	                cout << cy+left << " " << cx-i << "\n";
	                cout << cy+right << " " << cx+i << "\n";
	                left = nextL(left);
	                right = nextR(right);
	            }
	        }
	        //corners
	        if(cy+i <= n && cx+i <= m) {
	            cout << cy+i << " " << cx+i << "\n";
	            cout << cy-i << " " << cx-i << "\n";
	            cout << cy+i << " " << cx-i << "\n";
	            cout << cy-i << " " << cx+i << "\n";
	        }
	    }
	}
}