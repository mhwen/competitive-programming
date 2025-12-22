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

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int constexpr INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> sieve(1e7+5, INF);
	vector<int> nim(1e7+5);
	nim[0] = 0;
	nim[1] = 1;
	nim[2] = 0;
	int counter = 2;
	for(int i = 2; i < sz(sieve); i++) {
		if(sieve[i] == INF) {
			for(int j = i; j < sz(sieve); j+=i) {
				sieve[j] = min(sieve[j], i);
			}
			if(i == 2)
				continue;
			nim[i] = counter++;
		}
		else
			nim[i] = nim[sieve[i]];
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		int Xor = 0;
		for(int i = 0; i < n; i++) {
			int num;
			cin >> num;
			Xor ^= nim[num];
		}
		if(Xor)
			cout << "Alice\n";
		else
			cout << "Bob\n";
	}

}