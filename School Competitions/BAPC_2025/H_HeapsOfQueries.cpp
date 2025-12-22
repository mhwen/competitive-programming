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
	int q;
	cin >> q;
	while(q-->0) {
	    int n, x;
	    string s;
	    cin >> n >> x >> s;
	    int level = 1;
	    while(level <= x)
	        level *= 2;
	    level /= 2;
	    for(char c : s) {
	        if(c == 'U') {
	            if(level == 1) {
	                x = -1;
	                goto done;
	            }
	            else {
	                level /= 2;
	                if(x%(2*level) < level)
	                    x-= level;
	                else
	                    x -= 2*level;
	            }
	        }
	        else {
                int amt = n-(2*level-1);
                if(amt < 0) {
                    x = -1;
                    goto done;
                }
                int left = x+level;
                int right = x+2*level;
                
                int perLayer = amt/level;
                int overLayer = amt%level;
                int myLayer = x-level+1;
                int throughMe = perLayer;
                if(myLayer <= overLayer)
                    throughMe++;
                if(throughMe%2==0)
                    swap(left, right);
                if(c == 'L')
                    x = left;
                else
                    x = right;
                if(x > n) {
                    x = -1;
                    goto done;
                }
                level *= 2;
            }
	    }
	    done:
	    cout << x << "\n";
	}
}