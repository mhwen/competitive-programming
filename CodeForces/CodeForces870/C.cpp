#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> sieve(1e6+1, -1);
	for(int i = 2; i < (int)sieve.size(); i++) {
		if(sieve[i] == -1) {
			for(int j = i; j < (int)sieve.size(); j+=i) {
				if(sieve[j] == -1)
					sieve[j] = i;
			}
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		if(n == 1)
			cout << "YES\n";
		else {
			cout << (sieve[n] <= m ? "NO\n" : "YES\n");
		}
	}
}