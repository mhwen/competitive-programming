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

int rootn = 350;

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	
	vector<int> primes(3e5);
	vector<bool> squareFree(3e5, true);
	for(int i = 2; i < sz(primes); i++) {
		if(primes[i] == 0) {
			for(int mult = 1; i*mult < sz(primes); mult++) {
				primes[i*mult]++;
				if(mult%i==0)
					squareFree[i*mult] = false;
			}
		}
	}
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	vector<ll> nums(n+1);
	for(int i = 1; i <= n; i++)
		cin >> nums[i];
	vector<ll> below(rootn+1);
	for(int i = 1; i <= rootn; i++) {
		for(int mult = 1; i*mult <= n; mult++) {
			int j = i*mult;
			if(!squareFree[mult])
				continue;
			if(primes[mult]%2==0)
				below[i] += nums[j];
			else
				below[i] -= nums[j];
		}
	}
	while(q-->0) {
		int type;
		cin >> type;
		if(type == 1) {
			int id;
			ll val;
			cin >> id >> val;
			for(int i = 1; i <= rootn; i++) {
				if(id%i==0) {
					int mult = id/i;
					if(!squareFree[mult])
						continue;
					if(primes[mult]%2==0)
						below[i] += val-nums[id];
					else
						below[i] -= val-nums[id];
				}
			}
			nums[id] = val;
		}
		else {
			int i;
			cin >> i;
			if(i <= rootn)
				cout << below[i] << "\n";
			else {
				ll res = 0;
				for(int mult = 1; i*mult <= n; mult++) {
					int j = i*mult;
					if(!squareFree[mult])
						continue;
					if(primes[mult]%2==0)
						res += nums[j];
					else
						res -= nums[j];
				}
				cout << res << "\n";
			}
		}
	}
}