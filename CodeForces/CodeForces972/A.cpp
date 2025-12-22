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

char c[5] = {'a', 'e', 'i', 'o', 'u'};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		int amt = n/5;
		int extra = n%5;
		for(int i = 0; i < 5; i++) {
			for(int j = 0; j < amt; j++)
				cout << c[i];
			if(extra) {
				extra--;
				cout << c[i];
			}
		}
		cout << "\n";
	}
}