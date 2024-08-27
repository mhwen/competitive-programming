#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

bool good(vector<int>& a, vector<int>& b, int x) {
	return x+2 <= b[x] && x >= a[x+2];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<int> a(n+1);
	vector<int> b(n+1);
	for(int i = 1; i <= n; i++) {
		cin >> a[i] >> b[i];
	}
	int count = 0;
	for(int i = 1; i <= n-2; i++) {
		if(good(a, b, i)) {
			count++;
			i += 2;
		}
	}
	cout << count << "\n";
}