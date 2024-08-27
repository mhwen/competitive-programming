#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef long long ll;
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	ll pow = 1;
	ll bad = 1;
	for(int i = 0; i < n*m; i++) {
		pow = pow*2%MOD;
	}
	for(int i = 0; i < n+m-1; i++) {
		bad = bad*2%MOD;
	}
	cout << (pow-bad+MOD)%MOD << "\n";
}