#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string fb;
	for(int i = 1; i <= 300; i++) {
		if(i%3==0) {
			fb += 'F';
		}
		if(i%5==0) {
			fb += 'B';
		}
	}
	int t;
	cin >> t;
	while(t-->0) {
		int k;
		cin >> k;
		string s;
		cin >> s;
		if(fb.find(s) != string::npos) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
}