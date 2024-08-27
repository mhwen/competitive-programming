#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;


bool check(int use, vector<int>& a, vector<int>& b) {
	int n =(int)a.size();
	// cout << "checking " << use << " n=" << n << endl;
	for(int i = 0; i < use; i++) {
		// cout << "i " << i << " " << i+(n-use) << " ";
		// cout << "comparing " << a[i] << " " << b[i+(n-use)] << endl;
		if(a[i] >= b[i+(n-use)])
			return false;
	}
	// cout << "good" << endl;
	return true;
}

int check(vector<int>& a, vector<int>& b) {
	int n = (int)a.size();
	int left = 0, right = n;
	while(left <= right) {
		int mid = (left+right)/2;
		if(check(mid, a, b)) {
			left = mid+1;
		}
		else {
			right = mid-1;
		}
	}
	return n-right;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		vector<int> a(n);
		a[0] = 1;
		for(int i = 1; i < n; i++) {
			cin >> a[i];
		}
		vector<int> b(n);
		for(int i = 0; i < n; i++) {
			cin >> b[i];
		}
		// sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		
		vector<int> newA(n);
		for(int j = 1; j < n; j++) {
			newA[j] = a[j];
		}
		newA[0] = 1;
		sort(newA.begin(), newA.end());
		ll res = check(newA, b);
		
		int left = 1, right = m;
		while(left <= right) {

			int mid = (left+right)/2;
			for(int j = 1; j < n; j++) {
				newA[j] = a[j];
			}
			newA[0] = mid;
			sort(newA.begin(), newA.end());
			if(check(newA, b) == res) {
				left = mid+1;
			}
			else {
				right = mid-1;
			}
		}
		// cout << left << " " << right << endl;
		// cout << "change " << left << endl;
		

		cout << m*res + (m+1-left) << "\n";
	}
}