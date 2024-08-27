#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string alphabet;
	cin >> alphabet;
	string s;
	cin >> s;
	map<char, int> positions;
	for(int i = 0; i < 26; i++) {
		positions[alphabet[i]] = i;
	}
	int prev = -1;
	int count = 1;
	for(char c : s) {
		int pos = positions[c];
		if(pos <= prev)
			count++;
		prev = pos;
	}
	cout << count << "\n";
}