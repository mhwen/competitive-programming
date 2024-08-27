#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int val = 0;
	string s;
	cin >> s;
	for(char c : s)
		val += c-'0';
	cout << val << "\n";
}