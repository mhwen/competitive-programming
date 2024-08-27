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
		int n;
		cin >> n;
		int zeros = 0;
		int ones = 0;
		for(int i = 0; i < n; i++) {
			int a;
			cin >> a;
			if(a==0)
				zeros++;
			if(a==1)
				ones++;
		}
		if(zeros <= (n+1)/2)
			cout << 0 << "\n";
		else if(zeros == n)
			cout << 1 << "\n";
		else {
			if(ones+zeros < n)
				cout << 1 << "\n";
			else
				cout << 2 << "\n";
		}
	}
}