#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		ll total = 0;
		ll good = 1;
		for(int i = 1; i < n; i++) {
			int a;
			cin >> a;
			total = total*i%MOD;
			if(!a) {
				total = (total+good)%MOD;
				good = good*i%MOD;
			}
			else {
				good = good*(i-1)%MOD;
			}
			cout << total << " ";
		}
		cout << "\n";
	}
}