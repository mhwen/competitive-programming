#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		if(d < b) {
			cout << -1 << "\n";
			continue;
		}
		int newA = a+(d-b);
		if(newA < c) {
			cout << -1 << "\n";
			continue;
		}
		cout << d-b+newA-c << "\n";
	}
}