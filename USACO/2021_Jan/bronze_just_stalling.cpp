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
	int n;
	cin >> n;
	vector<int> cows(n);
	vector<int> stalls(n);
	for(int i = 0; i < n; i++) {
		cin >> cows[i];
	}
	for(int i = 0; i < n; i++) {
		cin >> stalls[i];
	}
	sort(cows.rbegin(), cows.rend());
	sort(stalls.rbegin(), stalls.rend());
	ll ways = 1;
	int availableStalls = 0;
	int stallId = 0;
	for(int cow : cows) {
		while(stallId < n && stalls[stallId] >= cow) {
			stallId++;
			availableStalls++;
		}
		ways = ways*availableStalls;
		availableStalls--;
	}
	cout << ways << "\n";
}