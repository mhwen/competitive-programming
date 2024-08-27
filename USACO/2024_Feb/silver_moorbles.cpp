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
		ll n;
		int m, k;
		cin >> n >> m >> k;
		vector<vector<ll>> evens(m);
		vector<vector<ll>> odds(m);
		for(int i = 0; i < m; i++) {
			for(int j = 0; j < k; j++) {
				ll val;
				cin >> val;
				if(val%2==0)
					evens[i].push_back(val);
				else
					odds[i].push_back(val);
			}
			sort(evens[i].begin(), evens[i].end());
			sort(odds[i].begin(), odds[i].end());
		}
		vector<ll> delta(m);
		vector<ll> remaining(m);
		ll curr = n;
		vector<string> choice(m);
		bool bad = false;
		multiset<ll> seen;
		//first we employ a strategy that maximizes the number of marbles we have
		//assuming the worst case scenario.
		//the worst case scenario is the only one we care about,
		//since the problem asks us to find a strategy that guarantees success,
		//which means it must work in all cases.
		//if we find a strategy that works in the worst case, then it will work for
		//all the other cases too.
		for(int i = 0; i < m; i++) {
			//there are two cases:
			//if the choices are all even or all odd, then we can guess even or odd
			//and be guaranteed to gain marbles.
			//the worst case scenario then is we gain the smallest choice of k
			if(evens[i].empty()) {
				choice[i] = "Odd";
				delta[i] = odds[i].front();
			}
			else if(odds[i].empty()) {
				choice[i] = "Even";
				delta[i] = evens[i].front();
			}
			//the other case is if there are both even and odd.
			//the worst case here is we are wrong and lose marbles.
			//if we guess even, then we lose the largest odd choice in the worst case.
			//if we guess odd, the we lose the largest even choice in the worst case.
			//to minimize the loss from the worst case, guess the one that minimizes our loss.
			else {
				if(evens[i].back() > odds[i].back()) {
					choice[i] = "Even";
					delta[i] = -odds[i].back();
				}
				else {
					choice[i] = "Odd";
					delta[i] = -evens[i].back();
				}
			}
			curr += delta[i];
			remaining[i] = curr;
			seen.insert(curr);
			if(curr <= 0) {
				bad = true;
				break;
			}
		}
		//if the strategy failed, then it is not possible to survive all the rounds
		if(bad) {
			cout << -1 << "\n";
			continue;
		}
		//otherwise, we can go from left to right
		//and try to change our strategy at each step to be
		//lexicographically smaller.
		//we are able to change only if the additional loss we incur from the
		//change doesn't cause us to lose in any future rounds.
		//we can do this check by keeping track of how many marbles we have
		//from each round in the future, and looking at the smallest value there.
		//if the amount we would lose is >= that value, then we know doing this
		//change will cause us to lose in the future, so we can't change
		//to do this check efficiently, we can use an array to keep track of
		//the minimum value of suffix segments of rounds, as well as a variable
		//keeping track of how much change we've incurred already.
		
		ll loss = 0;
		for(int i = 0; i < m; i++) {
			if(choice[i] == "Odd") {
				ll newDelta = -odds[i].back();
				ll diff = newDelta-delta[i];
				if(*seen.begin()+loss+diff > 0) {
					choice[i] = "Even";
					loss += diff;
				}
			}
			seen.erase(seen.find(remaining[i]));
		}
		for(int i = 0; i < m; i++) {
			if(i > 0)
				cout << " ";
			cout << choice[i];
		}
		cout << "\n";
	}
}