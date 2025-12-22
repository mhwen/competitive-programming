#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	map<int, int> counts;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		counts[a]++;
	}
	ll time = 0;
	ll remaining = n;
	for(auto entry : counts) {
		time += remaining;
		remaining -= entry.second;
	}
	cout << time << "\n";
}