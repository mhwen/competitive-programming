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
		int n, a, b;
		cin >> n >> a >> b;
		if(a+b < n) {
			if(a+b+1==n)
				cout << "No\n";
			else
				cout << "Yes\n";
		}
		else {
			if(a+b==2*n)
				cout << "Yes\n";
			else
				cout << "No\n";	
		}
	}
}