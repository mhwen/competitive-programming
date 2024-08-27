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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		string s;
		cin >> s;
		int left = 0, right = 0;
		int curr = 0;
		int dir = 1;
		for(int i = 0; i < n-1; i++) {
			if(s[i] == s[i+1])
				dir *= -1;
			else
				curr += dir;
			left = min(left, curr);
			right = max(right, curr);
		}
		cout << right-left+1 << "\n";
	}
}