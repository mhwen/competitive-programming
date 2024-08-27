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
	vector<pair<int, string>> blocks(n);
	for(int i = 0; i < n; i++) {
		cin >> blocks[i].first >> blocks[i].second;
	}
	sort(blocks.begin(), blocks.end());
	for(int i = 0; i < n; i++)
		cout << blocks[i].second << " ";
	cout << "\n";
}