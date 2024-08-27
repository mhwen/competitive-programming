#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> counts(3);
	for(int i = 0; i < 3; i++) {
		string line;
		getline(cin, line);
		stringstream ls(line);
		string s;
		while(getline(ls, s, ' '))
			counts[i]++;
	}
	int a = counts[0];
	int b = counts[1];
	int c = counts[2];
	cout << (a*(a-1)/2+a)*b*c << "\n";
}