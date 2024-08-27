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
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	vector<int> samp  {1, 2, 2, 3, 3, 4};
	vector<int> szSamp{1, 2, 2, 3, 3, 4};
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		if(n <= 6) {
			cout << szSamp[n-1] << "\n";
			for(int i = 0; i < n; i++)
				cout << samp[i] << " ";
			cout << "\n";
		}
		else {
			cout << 4 << "\n";
			for(int i = 0; i < n; i++)
				cout << i%4+1 << " ";
			cout << "\n";
		}
	}
}