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

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int p;
	cin >> p;
	
	auto check = [&](int num) {
		set<int> seen;
		while(num != 1) {
			if(seen.count(num))
				return false;
			seen.insert(num);
			int val = 0;
			while(num > 0) {
				val += (num%10)*(num%10);
				num /= 10;
			}
			num = val;
		}
		return true;
	};
	
	while(p-->0) {
		int t, n;
		cin >> t >> n;
		string happy = "YES";
		if(n == 1)
			happy = "NO";
			
		for(int i = 2; i*i <= n; i++) {
			if(n%i==0)
				happy = "NO";
		}
		
		if(!check(n))
			happy = "NO";
			
		cout << t << " " << n << " " << happy << "\n";
	}
}