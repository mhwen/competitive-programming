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
	string s;
	cin >> s;
	vector<int> need(n-1);
	int left = 0;
	for(int i = n-2; i >= 0; i--) {
		if(s[i] == 'R') {
			need[i] = 1;
			need[i] += left;
			left = 0;
		}
		else {
			need[i] = -1;
			left++;
		}
	}
	int curr = 1+left;
	int rightMost = curr;
	vector<int> ans{curr};
	for(int i : need) {
		if(i == -1)
			curr += i;
		else
			curr = rightMost+i;
		rightMost = max(rightMost, curr);
		ans.push_back(curr);
	}
	for(int i : ans)
		cout << i << "\n";
}