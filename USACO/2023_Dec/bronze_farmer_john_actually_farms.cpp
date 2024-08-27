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
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<ll> heights(n);
		for(int i = 0; i < n; i++) {
			cin >> heights[i];
		}
		vector<ll> grow(n);
		for(int i = 0; i < n; i++) {
			cin >> grow[i];
		}
		vector<int> order(n);
		for(int i = 0; i < n; i++) {
			int o;
			cin >> o;
			order[n-1-o] = i;
		}
		ll minTime = 0;
		ll maxTime = 5e18;
		bool bad = false;
		for(int i = 0; i < n-1; i++) {
			int left = order[i];
			int right = order[i+1];
			if(heights[left] < heights[right]) {
				//case 2
				if(grow[left] > grow[right]) {
					ll hDiff = heights[right]-heights[left];
					ll gDiff = grow[left]-grow[right];
					ll time = (hDiff-1)/gDiff;
					maxTime = min(maxTime, time);
				}
				//case 1
				else {//no need to do anything}
			}
			//heights[left] >= heights[right]
			else {
				//case 3
				if(grow[left] < grow[right]) {
					ll hDiff = heights[left]-heights[right]+1;
					ll gDiff = grow[right]-grow[left];
					ll time = (hDiff+gDiff-1)/gDiff;
					minTime = max(minTime, time);
				}
				//case 4
				else
					bad = true;
			}
		}
		if(bad || minTime > maxTime)
			cout << -1 << "\n";
		else
			cout << minTime << "\n";
	}
}