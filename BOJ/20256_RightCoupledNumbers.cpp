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
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		int found = 0;
		for(int a = 1; a*a <= x; a++) {
			if(x%a!=0)
				continue;
			int b = x/a;
			if(2*a >= b) {
				found = 1;
				break;
			}
		}
		cout << found << "\n";
	}
}