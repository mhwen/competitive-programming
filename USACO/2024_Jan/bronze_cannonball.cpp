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
	int n, s;
	cin >> n >> s;
	vector<int> val(n+1);
	vector<int> type(n+1);
	vector vis(3, vector<int>(n+1, -1));
	for(int i = 1; i <= n; i++) {
		cin >> type[i] >> val[i];
	}
	int curr = s;
	int dir = 1;
	int speed = 1;
	int count = 0;
	while(true) {
		if(curr < 1 || curr > n)
			break;
		if(vis[dir+1][curr] == speed)
			break;
		vis[dir+1][curr] = speed;
		if(type[curr] == 1) {
			if(val[curr] != -1 && speed >= val[curr]) {
				val[curr] = -1;
				count++;
			}
		}
		else {
			speed += val[curr];
			dir *= -1;
		}
		curr += dir*speed;
	}
	cout << count << "\n";
}