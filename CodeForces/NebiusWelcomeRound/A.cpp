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
		int a, b;
		cin >> a >> b;
		a = abs(a);
		b = abs(b);
		int diff = abs(a-b);
		if(diff > 1)
			cout << a+b+(diff-1) << "\n";
		else
			cout << a+b << "\n";
	}
}