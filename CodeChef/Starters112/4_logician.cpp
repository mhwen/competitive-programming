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
		int n;
		cin >> n;
		string s;
		cin >> s;
		bool no = false;
		int count = 0;
		for(char c : s) {
			if(c == '0') {
				no = true;
				cout << "NO\n";
			}
			else {
				count++;
				if(count == n)
					cout << "YES\n";
				else {
					if(no)
						cout << "NO\n";
					else
						cout << "IDK\n";
				}
			}
		}
	}
}