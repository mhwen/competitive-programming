#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	if(n%2==1) {
		cout << n << " " << n << "\n";
		n--;
	}
	if(n%6!=2) {
		for(int j = 1; j <= n/2; j++) {
			cout << j << " " << 2*j << "\n";
			cout << n/2+j << " " << 2*j-1 << "\n";
		}
	}
	else {
		for(int j = 1; j <= n/2; j++) {
			cout << j << " " << 1+(2*(j-1)+n/2-1)%n << "\n";
			cout << n+1-j << " " << n-(2*(j-1)+n/2-1)%n << "\n";
		}
	}
	
}