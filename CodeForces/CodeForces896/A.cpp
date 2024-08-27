#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

void outputPerm(int n, int offset) {
	for(int i = 0; i < n; i++) {
		cout << (i-offset+n)%n << " ";
	}
	cout << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		if(m == 1) {
			cout << 0 << "\n";
			for(int i = 0; i < n; i++)
				cout << 0 << "\n";
			continue;
		}
		if(m <= n)
			cout << m << "\n";
		else
			cout << n+1 << "\n";
		int count = 1;
		outputPerm(m, 0);
		for(int i = m; i <= n; i++) {
			count++;
			outputPerm(m, 0);
		}
		int offset = 1;
		while(count++ < n)
			outputPerm(m, offset++);
	}
	cout << "\n";
}