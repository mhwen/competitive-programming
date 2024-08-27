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
		int n, k;
		cin >> n >> k;
		string s;
		cin >> s;
		int b = 0;
		for(int i = 0; i < n; i++) {
			if(s[i] == 'B')
				b++;
		}
		if(b == k)
			cout << 0 << "\n";
		else {
			cout << 1 << "\n";
			if(b > k) {
				for(int i = 0; i < n; i++) {
					if(s[i] == 'B')
						b--;
					if(b == k) {
						cout << i+1 << " A\n";
						break;
					}
				}
			}
			else {
				for(int i = 0; i < n; i++) {
					if(s[i] == 'A')
						b++;
					if(b == k) {
						cout << i+1 << " B\n";
						break;
					}
				}
			}
		}
	}
}