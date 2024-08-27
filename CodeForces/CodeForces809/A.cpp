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
		int n, m;
		cin >> n >> m;
		vector<char> s(m, 'B');
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			a--;
			int left = min(a, m-a-1);
			int right = max(a, m-a-1);
			if(s[left] == 'A')
				s[right] = 'A';
			else
				s[left] = 'A';
		}
		cout << string(s.begin(), s.end()) << "\n";
	}	
}