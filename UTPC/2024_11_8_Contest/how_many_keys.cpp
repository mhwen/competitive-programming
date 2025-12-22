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
	vector<bool> white{1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1};
	int n;
	cin >> n;
	int w = 0, b = 0;
	int id = 0;
	int curr = 0;
	while(curr < n) {
		if(white[id]) {
			curr += 4;
			w++;
		}
		else {
			b++;
		}
		id = (id+1)%sz(white);
	}

	if(curr != n) {
		if(!white[(id+sz(white)-2)%sz(white)] && curr-3 == n && curr-3 >= 4)
			cout << w-1 << " " << b << "\n";
		else
			cout << -1 << "\n";
	}
	else
		cout << w << " " << b << "\n";
}