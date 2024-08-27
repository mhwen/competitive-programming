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
		string a, b;
		cin >> a >> b;
		if(a[0] == b[0]) {
			cout << "YES\n";
			cout << a[0] << "*\n";
			continue;
		}
		if(a.back() == b.back()) {
			cout << "YES\n";
			cout << "*" << a.back() << "\n";
			continue;
		}
		bool found = false;
		string ans = "";
		for(int i = 0; i+1 < (int)a.length(); i++) {
			for(int j = 0; j+1 < (int)b.length(); j++) {
				if(a[i] == b[j] && a[i+1] == b[j+1]) {
					found = true;
					ans += a[i];
					ans += a[i+1];
					goto A;
				}
			}

		}
		A:
		if(found) {
			cout << "YES\n";
			cout << "*" << ans << "*\n";
		}
		else {
			cout << "NO\n";
		}
	}
}