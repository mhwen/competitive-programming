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
typedef long double ld;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ld> x(10);
	vector<ld> y(10);
	for(int i = 0; i < 10; i++)
		cin >> x[i] >> y[i];
	
	function<bool(int, int, int)> colinear = [&](int a, int b, int c) {
		if(x[a] == x[b] && x[b] == x[c])
			return true;
		if(y[a] == y[b] && y[b] == y[c])
			return true;
		return false;
	};
	
	bool found = false;
	for(int i = 0; i < 10; i++) {
		for(int j = i+1; j < 10; j++) {
			for(int k = j+1; k < 10; k++) {
				if(colinear(i, j, k))
					found = true;
			}
		}
	}
	if(found)
		cout << "CASSETTE\n";
	else
		cout << "VINYL\n";
}