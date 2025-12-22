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
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		vector<int> nums(n);
		for(int i = 0; i < n; i++)
			cin >> nums[i];
		vector<int> s = nums;
		sort(all(s));
		map<pair<int, int>, queue<int>> curr;
		for(int i = 0; i < n; i++) {
			curr[{nums[i], s[i]}].push(i);
		}
		vector<pair<int, int>> moves;
		auto move = [&](pair<int, int> a, pair<int, int> b) {
			assert(!curr[a].empty() && !curr[b].empty());
			auto A = curr[a].front();
			curr[a].pop();
			auto B = curr[b].front();
			curr[b].pop();
			moves.emplace_back(A+1, B+1);
			assert(nums[A]-nums[B] == 1);
			nums[B]++;
			nums[A]--;
			pair<int, int> newA = {a.first-1, a.second};
			curr[newA].push(A);
			pair<int, int> newB = {b.first+1, b.second};
			curr[newB].push(B);
			assert(sz(moves) <= n);
		};
		while(true) {
			bool moved = false;
			while(!curr[{2,0}].empty() && !curr[{1,2}].empty()) {
				move({2,0},{1,2});
				moved = true;
			}
			while(!curr[{1,0}].empty() && !curr[{0,2}].empty()) {
				move({1,0},{0,2});
				moved = true;
			}
			if(!moved)
				break;
		}
		while(!curr[{2,0}].empty()) {
			if(curr[{1,0}].empty())
				move({1,1},{0,2});
			else
				move({1,0},{0,2});
			move({2,0},{1,2});
		}
		assert((curr[{1,2}].size()==curr[{2,1}].size()));
		assert((curr[{1,0}].size()==curr[{0,1}].size()));
		while(!curr[{1,2}].empty())
			move({2,1},{1,2});
		while(!curr[{1,0}].empty())
			move({1,0},{0,1});
		cout << sz(moves) << "\n";
		for(auto[a,b] : moves)
			cout << a << " " << b << "\n";
		for(int i = 0; i < n; i++)
			assert(nums[i] == s[i]);
	}
}