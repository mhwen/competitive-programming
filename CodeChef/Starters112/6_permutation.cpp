#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, x;
		cin >> n >> x;
		if(n%2==1) {
			if(x != n/2+1) {
				vector<int> front;
				vector<int> back;
				for(int i = min(x, n-x+1); i <= n/2; i++) {
					front.push_back(i);
					back.push_back(n-i+1);
				}
				for(int i = 1; i < min(x, n-x+1); i++) {
					front.push_back(i);
					back.push_back(n-i+1);
				}
				if(x > n/2)
					swap(front, back);
				reverse(back.begin(), back.end());
				for(int i : front)
					cout << i << " ";
				cout << n/2+1 << " ";
				for(int i : back)
					cout << i << " ";
				cout << "\n";
			}
			else {
				cout << -1 << "\n";
			}
		}
		else {
			vector<int> front;
			vector<int> back;
			for(int i = min(x, n-x+1); i <= n/2; i++) {
				front.push_back(i);
				back.push_back(n-i+1);
			}
			for(int i = 1; i < min(x, n-x+1); i++) {
				front.push_back(i);
				back.push_back(n-i+1);
			}
			if(x > n/2)
				swap(front, back);
			reverse(back.begin(), back.end());
			for(int i : front)
				cout << i << " ";
			for(int i : back)
				cout << i << " ";
			cout << "\n";
		}
	}
}