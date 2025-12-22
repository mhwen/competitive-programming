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

//https://codeforces.com/group/ejaj3Dzoql/contest/544965

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	int Xor = 0;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		Xor ^= (a-2);
	}
	string first;
	cin >> first;
	if(first == "Whiteking") {
		if(Xor)
			cout << "Whiteking\n";
		else
			cout << "Blackking\n";
	}
	else {
		if(Xor)
			cout << "Blackking\n";
		else
			cout << "Whiteking\n";
	}
}