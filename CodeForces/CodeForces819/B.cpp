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
		int n, m;
		cin >> n >> m;
		if(n > m)
			cout << "No\n";
		else if(n%2==0) {
			if(m%2==1)
				cout << "No\n";
			else {
				cout << "Yes\n";
				for(int i = 0; i < n-2; i++) {
					cout << "1 ";
				}
				cout << (m-n+2)/2 << " " << (m-n+2)/2 << "\n";
			}
		}
		else {
			cout << "Yes\n";
			for(int i = 0; i < n-1; i++) {
				cout << "1 ";
			}
			cout << m-n+1 << "\n";
		}
		
	}
}