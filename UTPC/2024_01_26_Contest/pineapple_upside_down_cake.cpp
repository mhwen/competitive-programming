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
	int sz = 1;
	int prev = 0;
	while(true) {
		cout << "? " << sz << endl;
		int res;
		cin >> res;
		if(res <= prev) {
			sz /= 2;
			break;
		}
		prev = res;
		sz = sz*2;
	}
	int left = sz;
	int right = sz*2-1;
	while(left <= right) {
		int mid = (left+right)/2;
		cout << "? " << mid << endl;
		int res;
		cin >> res;
		if(res < prev) {
			right = mid-1;
		}
		else {
			prev = res;
			left = mid+1;
		}
	}
	cout << "! " << right << endl;
}