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
	    int a, b, c, t;
	    cin >> a >> b >> c >> t;
	    int aTimes = t/a;
	    int bTimes = t/b;
	    int cTimes = t/c;

	    ld totPow = aTimes*log(2)+bTimes*log(0.85);
	    ld pow = aTimes*log(2)+bTimes*log(0.85)+cTimes*log(0.9);
	    ld ans = exp(totPow)-exp(pow);
	    if(isnan(ans))
	        ans = 0;
	    cout << fixed << setprecision(20);
	    cout << ans << "\n";
	}
}