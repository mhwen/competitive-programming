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
#define rep(i, a, b) for(int i = a; i < (b); i++)
typedef vector<int> vi;
typedef pair<int, int> pii;

const int LIM = 5e8;
bitset<LIM> isPrime;
vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pii> cp;
	for(int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for(int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for(int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		
		rep(i,0,min(S, R - L))
			if(!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for(int i : pr) isPrime[i] = 1;
	return pr;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	auto primes = eratosthenes();
	int n;
	cin >> n;
	vector<bool> bad(10);
	for(int i = 0; i < n; i++) {
		int dig;
		cin >> dig;
		bad[dig] = true;
	}
	auto check = [&](int num) {
		while(num > 0) {
			if(bad[num%10])
				return false;
			num /= 10;
		}
		return true;
	};
	for(int i : primes) {
		if(check(i)) {
			cout << i << "\n";
			return 0;
		}
	}
	cout << -1 << "\n";
}