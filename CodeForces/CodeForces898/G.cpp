#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		s = 'B'+s+'B';
		char prev = 'A';
		int curr = (int)s.length();
		bool doubleB = false;
		int aSum = 0;
		int smallestA = (int)s.length();
		for(char c : s) {
			if(c == 'A') {
				curr++;
				aSum++;
			}
			else {
				if(prev == 'B')
					doubleB = true;
				else {
					smallestA = min(smallestA, curr);
					curr = 0;
				}
			}
			prev = c;
		}

		if(doubleB)
			cout << aSum << "\n";
		else
			cout << aSum - smallestA << "\n";
	}
}