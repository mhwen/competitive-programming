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
	vector<ll> volumes(n);
	for(int i = 0; i < n; i++) {
		cin >> volumes[i];
	}
	vector<ll> remaining(n);
	for(int i = n-2; i >= 0; i--) {
		remaining[i] = remaining[i+1]+volumes[i+1];
	}
	vector<ll> timeNeeded(n);
	ll prevTime = 0;
	ll prevVolume = 0;
	for(int i = 0; i < n; i++) {
		ll amount = (i+1)*prevTime;
		ll extra = amount-prevVolume;
		if(extra >= volumes[i]) {
			extra -= volumes[i];
			ll needed = max(0LL, remaining[i]-extra);
			timeNeeded[i] = prevTime+(needed+i)/(i+1);
		}
		else {
			ll needed = remaining[i]+volumes[i]-extra;
			timeNeeded[i] = prevTime+(needed+i)/(i+1);
			prevTime += (volumes[i]-extra+i)/(i+1);
		}
		prevVolume += volumes[i];
	}
	int q;
	cin >> q;
	while(q-->0) {
		ll time;
		cin >> time;
		auto it = upper_bound(timeNeeded.rbegin(), timeNeeded.rend(), time);
		if(it == timeNeeded.rbegin()) {
			cout << -1 << "\n";
		}
		else {
			int pos = (int)(timeNeeded.rend()-it);
			cout << pos+1 << "\n";
		}
	}
}