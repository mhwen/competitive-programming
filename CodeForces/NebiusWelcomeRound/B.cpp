#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k, d, w;
		cin >> n >> k >> d >> w;
		ll times[n];
		for(int i = 0; i < n; i++) {
			cin >> times[i];
		}
		int packs = 1;
		int used = 1;
		ll prevTime = times[0]+w;
		for(int i = 1; i < n; i++) {
			// cout << i << " " << used << " " << prevTime << "\n";
			if(used >= k || times[i]>prevTime+d) {
				packs++;
				prevTime = times[i]+w;
				used = 1;
			}
			else {
				used++;
			}
		}
		cout << packs << "\n";
		
	}
}