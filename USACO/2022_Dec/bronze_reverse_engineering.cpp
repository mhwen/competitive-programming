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
		int n, m;
		cin >> n >> m;
		vector<string> s(m);
		vector<int> results(m);
		for(int i = 0; i < m; i++) {
			cin >> s[i] >> results[i];
		}
		vector<bool> eliminated(m);
		//we can think about greedily building our program as we go
		//while we can insert an if statement that eliminates some inputs, then we do so
		while(true) {
			bool foundElimination = false;
			//check each variable to see if we can use that variable in the next if statement
			for(int var = 0; var < n; var++) {
				vector<int> one;
				vector<int> zero;
				for(int str = 0; str < m; str++) {
					if(eliminated[str])
						continue;
					if(s[str][var] == '1')
						one.push_back(str);
					else
						zero.push_back(str);
				}
				bool oneAllSame = true;
				for(int i = 0; i < (int)one.size()-1; i++) {
					if(results[one[i]] != results[one[i+1]]) {
						oneAllSame = false;
					}
				}
				
				bool zeroAllSame = true;
				for(int i = 0; i < (int)zero.size()-1; i++) {
					if(results[zero[i]] != results[zero[i+1]]) {
						zeroAllSame = false;
					}
				}
				
				//if all the remaining inputs that have this variable set to 1 all evaluate to the same thing,
				//then we can insert an if statement to eliminate all these inputs
				if(oneAllSame) {
					for(int i : one)
						eliminated[i] = true;
					if((int)one.size() > 0)
						foundElimination = true;
				}
				//same idea for all remaining inputs that have this variable set to 0
				if(zeroAllSame) {
					for(int i : zero)
						eliminated[i] = true;
					if((int)zero.size() > 0)
						foundElimination = true;
				}
			}
			//if there is no possible if statement left to insert that can eliminate inputs, we stop
			if(!foundElimination)
				break;
		}
		
		//the runtime of this algorithm is O(nm^2),
		//since it takes O(nm) time to find an if statement to insert,
		//and we will insert at most m if statements, since each one we insert
		//eliminates at least one input, and there are only m inputs in total.

		int elimCount = 0;
		for(bool b : eliminated)
			if(b)
				elimCount++;
		//if we eliminated all inputs we win
		if(elimCount == m)
			cout << "OK\n";
		else
			cout << "LIE\n";
	}
}