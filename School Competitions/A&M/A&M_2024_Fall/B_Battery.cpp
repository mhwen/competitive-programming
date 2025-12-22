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
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	int flips = 0;
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int curr = 0;
		if(s == "ON")
			curr = 1;
		if((curr+flips)%2==0)
			flips++;
	}
	cout << flips << "\n";
}