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
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		if(nums[0] == nums[n-1])
			cout << "NO\n";
		else {
			cout << "YES\n";
			if(nums[0] != nums[n-2]) {
				for(int i = 0; i < n-1; i++)
					cout << "B";
				cout << "R";
				cout << "\n";
			}
			else {
				cout << "R";
				for(int i = 0; i < n-1; i++)
					cout << "B";
				cout << "\n";
			}

		}
	}
}