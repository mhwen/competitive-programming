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

ll gcd(ll a, ll b) {
	if(b==0)
		return a;
	return gcd(b, a%b);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll a, b;
		cin >> a >> b;
		if(b%a==0)
			cout << b/a*b << "\n";
		else
			cout << a/gcd(a,b)*b << "\n";
	}
	
}