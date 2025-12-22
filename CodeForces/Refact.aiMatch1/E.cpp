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

int main() {
	vector<vector<int>> factors(4e5+5);
	for(int i = 2; i < sz(factors); i++) {
		if(sz(factors[i]) == 0) {
			for(int j = i; j < sz(factors); j+=i) {
				factors[j].push_back(i);
			}
		}
	}
	auto isPrime = [&](int num) {
		return factors[num].front() == num;
	};
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		sort(all(nums));
		int primes = 0;
		for(int i : nums) {
			if(isPrime(i))
				primes++;
		}
		if(primes == 0) {
			cout << 2 << "\n";
		}
		else if(primes > 1) {
			cout << -1 << "\n";
		}
		else {
			if(!isPrime(nums.front())) {
				cout << -1 << "\n";
			}
			else {
				int v = nums.front();
				set<int> bad;
				auto check = [&]() {
					vector<bool> vis(1000);
					vis[0] = true;
					for(int i = 0; i < sz(vis); i++) {
						if(2*v+i >= sz(factors))
							break;
						if(!vis[i])
							continue;
						for(int f : factors[2*v+i]) {
							if(2*v+i+f < sz(factors) && i+f < sz(vis)) {
								vis[i+f] = true;
							}
						}
					}
					for(int i = 0; i < sz(vis); i++) {
						if(2*v+i >= sz(factors))
							break;
						if(!vis[i] && !isPrime(2*v+i))
							bad.insert(2*v+i);
					}
				};
				check();
				bool good = true;
				for(int i : nums) {
					if(i > v && i < 2*v)
						good = false;
					if(bad.count(i))
						good = false;
				}
				if(good)
					cout << v << "\n";
				else
					cout << -1 << "\n";
			}
		}
	}

}