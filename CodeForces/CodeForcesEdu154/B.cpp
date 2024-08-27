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
		int n = (int)a.length();
		bool good = false;
		for(int i = 0; i < n-1; i++) {
			if(a[i] == '0' && a[i+1] == '1' && b[i] == '0' && b[i+1] == '1')
				good = true;
		}
		if(good)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}