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

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<ll> twoPow(n+1);
	twoPow[0] = 1;
	for(int i = 1; i < sz(twoPow); i++)
	    twoPow[i] = twoPow[i-1]*2%MOD;
    stack<pair<int, int>> a;
    ll ans = 1;
    for(int i = 1; i <= n; i++) {
        int num;
        cin >> num;
        while(!a.empty() && a.top().first < num)
            a.pop();
        if(a.empty())
            ans = ans*twoPow[i-1]%MOD;
        else {
            int left = a.top().second-1;
            int right = i-a.top().second;
            ans = ans*twoPow[left]%MOD*(twoPow[right]-1)%MOD;
        }
        a.push({num, i});
    }
	cout << ans << "\n";
}