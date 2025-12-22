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
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	int right = 0;
	int cnt = 0;
	int best = 0;
	for(int left = 0; left < n; left++) {
		while(right < n && cnt+(s[right]=='2') <= k) {
			if(s[right] == '2')
				cnt++;
			right++;
		}
		best = max(best, right-left);
		if(s[left] == '2')
			cnt--;
	}
	cout << best << "\n";
	
}