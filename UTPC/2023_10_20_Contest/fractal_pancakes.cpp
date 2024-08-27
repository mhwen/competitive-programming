#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr ll MOD = 1e9+7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	ll sides = 1;
	for(int i = 1; i <= n; i++) {
		if(i%2==1) {
			sides = (sides*4-1)%MOD;
		}
		else {
			sides = (sides*4+1)%MOD;
		}
	}
	cout << sides << "\n";
}