#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	int y = 0;
	int vow = 0;
	for(char c : s) {
		if(c == 'y')
			y++;
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			vow++;
	}
	cout << vow << " " << vow+y << "\n";
}