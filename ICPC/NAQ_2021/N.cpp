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
constexpr ll MOD = 1131415926535897LL;
constexpr ll P = 2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	map<string, int> seen;
	vector<vector<int>> sets(n);
	vector<int> remaining(4000);
	int id = 0;
	for(int i = 0; i < n; i++) {
		int k;
		cin >> k;
		for(int j = 0; j < k; j++) {
			string s;
			cin >> s;
			if(seen.count(s) == 0) {
				seen[s] = id++;
			}
			sets[i].push_back(seen[s]);
			remaining[seen[s]]++;
		}
	}
	int numSets = (int)seen.size();
	vector<int> begins(numSets);
	vector<int> ends(numSets);
	vector<string> names(numSets);
	for(auto s: seen)
		names[seen[s.first]] = s.first;
		
	// for(int i = 0; i < numSets; i++) {
		// cout << i << " " << names[i] << " " << remaining[i] << endl;
	// }
		
	vector<ll> pows(numSets);
	pows[0] = 1;
	for(int i = 1; i < numSets; i++) {
		pows[i] = pows[i-1]*P%MOD;
	}
	
	function<ll(ll, int)> setBit = [&](ll val, int bit) {
		return (val+pows[bit])%MOD;
	};
	function<ll(ll, int)> unsetBit = [&](ll val, int bit) {
		return (val-pows[bit]+MOD)%MOD;
	};
	
	set<ll> hashedSets;
	for(int i = 0; i < n; i++) {
		ll val = 0;
		for(int bit : sets[i]) {
			val = setBit(val, bit);
		}
		if(hashedSets.count(val))
			return -1;
		hashedSets.insert(val);
	}
	
	// cout << "hashed sets ";
	// for(ll val : hashedSets)
		// cout << val << " ";
	// cout << endl;
	
	int index = 1;
	
	function<bool(int)> assign = [&](int startSet) {
		
		queue<int> q;
		vector<bool> inCurr(numSets);
		int start = sets[startSet][0];
		// cout << "assigning " << names[start] << " " << startSet << endl;
		q.push(start);
		inCurr[start] = true;
		begins[start] = index++;
		ll currVal = pows[start];
		hashedSets.erase(currVal);
		remaining[start]--;
		
		while(currVal != 0) {
			// cout << endl;
			// cout << "currVal " << currVal << endl;
			vector<int> unset;
			for(int bit = 0; bit < numSets; bit++) {
				if(inCurr[bit] && remaining[bit] == 0) {
					unset.push_back(bit);
				}
			}
			
			// cout << "unset ";
			// for(int i : unset)
				// cout << names[i] << " ";
			// cout << endl;
			
			if((int)unset.size() > 1)
				return false;
			else if((int)unset.size() == 1) {
				int uVal = unset[0];
				// cout << "qval " << names[q.front()] << endl;
				if(q.front() != uVal)
					return false;
				currVal = unsetBit(currVal, uVal);
				// cout << "new val " << currVal << endl;
				q.pop();
				inCurr[uVal] = false;
				if(hashedSets.count(currVal) == 0) {
					ends[uVal] = index;
					continue;
				}
				else {
					hashedSets.erase(currVal);
					for(int bit = 0; bit < numSets; bit++) {
						if(inCurr[bit]) {
							remaining[bit]--;
						}
					}
					ends[uVal] = index++;
					// cout << "unsetted " << names[uVal] << " " << uVal << endl;
				}
			}
			else {
				vector<int> next;
				for(int bit = 0; bit < numSets; bit++) {
					if(!inCurr[bit]) {
						if(hashedSets.count(setBit(currVal, bit))) {
							next.push_back(bit);
						}
					}
				}
				
				// cout << "next ";
				// for(int i : next)
					// cout << names[i] << " ";
				// cout << endl;
				
				if((int)next.size() != 1)
					return false;
					
				int sVal = next[0];
				currVal = setBit(currVal, sVal);
				hashedSets.erase(currVal);
				inCurr[sVal] = true;
				q.push(sVal);
				for(int bit = 0; bit < numSets; bit++) {
					if(inCurr[bit])
						remaining[bit]--;
				}
				begins[sVal] = index++;
				// cout << "setted " << names[sVal] << " " << sVal << endl;
			}
		}
		
		// if(!q.empty())
			// cout << "q not empty " << q.front() << endl;
		
		return q.empty();
	};
	
	bool bad = false;
	
	for(int i = 0; i < n; i++) {
		if((int)sets[i].size() > 1)
			continue;
		int start = sets[i][0];
		if(remaining[start] == 0)
			continue;
		ll val = pows[start];
		int next = 0;
		for(int bit = 0; bit < numSets; bit++) {
			if(bit == start)
				continue;
			if(hashedSets.count(setBit(val, bit)))
				next++;
		}
		if(next <= 1) {
			if(!assign(i)) {
				bad = true;
				break;
			}
		}
	}
	
	// cout << "hashed sets at end ";
	// for(ll val : hashedSets)
		// cout << val << " ";
	// cout << endl;
	
	if((int)hashedSets.size() > 0)
		bad = true;
	
	if(bad)
		cout << "IMPOSSIBLE\n";
	else {
		for(int i = 0; i < numSets; i++) {
			cout << names[i] << " " << begins[i] << " " << ends[i] << "\n";
		}
	}

	
}