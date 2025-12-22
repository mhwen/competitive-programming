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
#include <bitset>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

constexpr int MX = 20*1e6;

bitset<MX*2+1> dp, ans;
const int zero = MX;

int main() {
	int n;
	cin >> n;
    vector<int> arr(n);
    for(int& x : arr) cin >> x;
    if(n >= 20) {
    	cout << 0 << "\n";
    	return 0;
    }
    dp[zero] = true;
    for(int i = 0; i<n; i++){
        ans |= dp << arr[i];
        ans |= dp >> arr[i];
        dp |= ans;
    }
    int A = 20;
    for(int i = 0; i<MX; i++){
        if(ans[zero+i] == true)
            A = min(A, __builtin_popcount(i));
    }
    cout << A << "\n";
}