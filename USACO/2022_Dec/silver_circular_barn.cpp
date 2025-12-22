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
#define pb push_back

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<bool> prime(5e6+5, true);
	prime[0] = false;
	for(int i = 2; i < sz(prime); i++) {
	    if(prime[i]) {
	        for(int j = i+i; j < sz(prime); j+=i)
	            prime[j] = false;
	    }
	}
	vector<int> moves(sz(prime), INF);
	moves[0] = 0;
	vector<int> primes(4, -1);
	for(int i = 1; i < sz(moves); i++) {
	    if(prime[i])
	        primes[i%4] = i;
	    if(i%2==0)
	        moves[i] = i/2;
	    else {
	        for(int o = 0; o < 4; o++) {
	            if(primes[o] == -1)
	                continue;
	            if((i-o)%4!=0)
	                continue;
	            moves[i] = min(moves[i], moves[i-primes[o]]+1);
	        }
	    }
	}
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<int> a(n);
	    int mn = INF;
	    for(int i = 0; i < n; i++) {
	        cin >> a[i];
	        mn = min(mn, moves[a[i]]);
	    }
	    for(int i = 0; i < n; i++) {
	        if(moves[a[i]] == mn || moves[a[i]] == (mn^1)) {
	            if(a[i]%4==0)
	                cout << "Farmer Nhoj\n";
	            else
	                cout << "Farmer John\n";
	            break;
	        }
	    }
	    
	}
}