#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

typedef long double ld;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<ld> nums(3);
	for(int i = 0; i < 3; i++)
		cin >> nums[i];
	sort(all(nums));
	
	auto check = [&](ld H) {
		ld sinX = nums[1]/H;
		ld sinY = nums[2]/H;
		ld x = asin(sinX);
		ld y = asin(sinY);
		ld checkH = nums[0]/tan(x)+nums[0]/tan(y);
		return abs(H-checkH);
	};
	
	ld lo = max(nums[1], nums[2]), hi = 1e9;
	for(int i = 0; i < 1000; i++) {
		ld m1 = lo+(hi-lo)/3;
		ld m2 = lo+2*(hi-lo)/3;
		if(check(m1) < check(m2))
			hi = m2;
		else
			lo = m1;
	}
	ld H = (lo+hi)/2;
	cout << fixed << setprecision(20) << nums[0]*H/2 << "\n";
	
}