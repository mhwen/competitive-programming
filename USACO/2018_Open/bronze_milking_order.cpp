#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	freopen("milkorder.in", "r", stdin);
	freopen("milkorder.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> h(m);
	int onePos = -1;
	for(int i = 0; i < m; i++) {
		cin >> h[i];
		if(h[i] == 1)
			onePos = i;
	}
	vector<int> positions(n+1);
	for(int i = 0; i < k; i++) {
		int c, p;
		cin >> c >> p;
		if(c == 1) {
			cout << p << "\n";
			return 0;
		}
		positions[p] = c;
	}

	int prevhPos = -1, prevIndex = 1, free = 0;
	for(int i = 1; i <= n; i++) {
		if(positions[i] == 0) {
			free++;
			if(free == 1)
				prevIndex = i;
			continue;
		}
		int hPos = -1;
		for(int j = 0; j < m; j++) {
			if(h[j] == positions[i])
				hPos = j;
		}
		if(hPos != -1) {
			if(onePos == -1 && hPos-prevhPos-1 < free) {
				cout << prevIndex << "\n";
				return 0;
			}
			if(onePos != -1 && onePos < hPos) {
				int diff = onePos-prevhPos;
				for(int j = prevIndex;;j++) {
					if(positions[j] == 0)
						diff--;
					if(diff==0) {
						cout << j << "\n";
						return 0;
					}
				}
				return 0;
			}
			free = 0;
			prevhPos = hPos;
		}
		
	}
	if(onePos == -1)
		cout << prevIndex << "\n";
	else {
		int diff = onePos-prevhPos;
		for(int j = prevIndex;;j++) {
			if(positions[j] == 0)
				diff--;
			if(diff==0) {
				cout << j << "\n";
				return 0;
			}
		}
	}
	
}