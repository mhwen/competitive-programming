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

void print128(__int128 num) {
	if(num == 0) {
		cout << "0\n";
		return;
	}
	string res;
	while(num > 0) {
		int digit = (int)(num%10);
		res += to_string(digit);
		num/=10;
	}
	reverse(res.begin(), res.end());
	cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<__int128> nums(n);
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		__int128 val = 0;
		for(char c : s) {
			int digit = c-'0';
			val = val*10+digit;
		}
		nums[i] = val;
	}
	__int128 pow = 1;
	for(int i = 0; i <= 127; i++) {
		vector<__int128> newNums;
		for(auto num : nums) {
			if(num != pow)
				newNums.push_back(num);
			else {
				if(!newNums.empty() && newNums.back() == pow)
					newNums.back() *= 2;
				else
					newNums.push_back(num);
			}
		}
		
		vector<__int128> strippedNewNums;
		for(auto num : newNums) {
			if(num != pow)
				strippedNewNums.push_back(num);
		}
		if(strippedNewNums.empty()) {
			print128(newNums[0]);
			break;
		}
		pow *= 2;
		nums = strippedNewNums;
	}
}