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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	vector<int> nums;
	nums.push_back(1);
	if(n >= 2)
		nums.push_back(2);
	if(n <= 2) {
		if(m == 0) {
			for(int i : nums)
				cout << i << " ";
			cout << "\n";
		}
		else {
			cout << -1 << "\n";
		}
	}
	else {
		for(int i = 3; i <= n; i++) {
			if((i-1)/2 <= m) {
				m -= (i-1)/2;
				nums.push_back(i);
			}
			else if(m > 0) {
				for(int start = 1; start <= i-1; start++) {
					if((i-start)/2 == m) {
						nums.push_back(i+start-1);
						break;
					}
				}
				m = 0;
			}
			else {
				nums.push_back((int)1e9-3*n*(n-i));
			}
		}
		if(m != 0)
			cout << -1 << "\n";
		else {
			for(int i : nums)
				cout << i << " ";
			cout << "\n";
		}
	}

}