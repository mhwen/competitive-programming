#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> sieve(1e7+1, -1);
	for(int i = 2; i < (int)sieve.size(); i++) {
		if(sieve[i] == -1) {
			for(int j = i; j < (int)sieve.size(); j+= i) {
				sieve[j] = i;
			}
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		map<int, int> counts;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			while(a != 1) {
				counts[sieve[a]]++;
				a /= sieve[a];
			}
		}
		ll extra = 0;
		ll ans = 0;
		for(auto c : counts) {
			ans += c.second/2;
			extra += c.second%2;
		}
		ans += extra/3;
		cout << ans << "\n";
	}
}