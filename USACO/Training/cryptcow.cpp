/*
ID: markhwe1
TASK: cryptcow
LANG: C++17
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <random>
#include <chrono>
#include <unordered_set>
#include <fstream>

using namespace std;

typedef long long ll;

#define sz(x) (int)(x).size()

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randval(int n) {
	return uniform_int_distribution(0, n)(rng);
}

string message = "Begin the Escape execution at the Break of Dawn";
set<ll> seen;
hash<string> hs;
map<char, int> sCounts;
map<char, int> counts;

string operate(int a, int b, int c, string& s) {
	string left = "";
	string midL = "";
	string midR = "";
	string right = "";
	for(int i = 0; i < (int)s.size(); i++) {
		if(i < a)
			left += s[i];
		else if(i < a+b)
			midL += s[i];
		else if(i < a+b+c)
			midR += s[i];
		else
			right += s[i];
	}
	return left+"C"+midR+"O"+midL+"W"+right;
}

string genRand(int _sz) {
	string s = message;
	for(int i = 0; i < _sz; i++) {
		vector<int> ids;
		for(int j = 0; j < 3; j++)
			ids.push_back(randval(sz(s)+1));
		sort(ids.begin(), ids.end());
		s = operate(ids[0], ids[1]-ids[0], ids[2]-ids[3], s);
	}
	cout << s << endl;
	return s;
}

bool isCOW(char c) {
	return c == 'C' || c == 'O' || c == 'W';
}

bool check(string s) {
	int prev = 0;
	for(int i = 0; i < sz(s); i++) {
		if(isCOW(s[i])) {
			string tmp = s.substr(prev, i-prev);
			if(message.find(tmp) == string::npos)
				return false;
			prev = i+1;
		}
	}
	string tmp = s.substr(prev, sz(s)-prev);
	if(message.find(tmp) == string::npos)
		return false;
		
	for(int i = 0; i < sz(s); i++) {
		if(s[i] == 'C')
			break;
		if(s[i] != message[i])
			return false;
	}
	int t = sz(message)-1;
	for(int i = sz(s)-1; i >= 0; i--) {
		if(s[i] == 'W')
			break;
		if(s[i] != message[t])
			return false;
		t--;
	}
	return true;
}

bool search(string curr) {
	if(sz(curr) == sz(message))
		return curr == message;

	for(int i = 0; i < sz(curr); i++) {
		if(curr[i] != 'C')
			continue;
		for(int j = i+1; j < sz(curr); j++) {
			if(curr[j] != 'O')
				continue;
			for(int h = j+1; h < sz(curr); h++) {
				if(curr[h] != 'W')
					continue;
				string next = curr.substr(0, i) + curr.substr(j+1, h-j-1) + curr.substr(i+1, j-i-1) + curr.substr(h+1, sz(curr)-h-1);
				if(check(next)) {
					ll hash = hs(next);
					if(seen.count(hash))
						continue;
					seen.insert(hash);
					if(search(next))
						return true;
				}

			}
		}
	}
	return false;
}


int main() {
	ofstream cout("cryptcow.out");
    ifstream cin("cryptcow.in");
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	for(char c : message)
		counts[c]++;
	
	string s;
	getline(cin, s);
	
	// s = genRand(9);
	
	int C = 0, O = 0, W = 0;
	for(char c : s) {
		if(c == 'C')
			C++;
		else if(c == 'O')
			O++;
		else if(c == 'W')
			W++;
		else
			sCounts[c]++;
	}
	if(sCounts != counts || C!=O || O!=W) {
		cout << 0 << " " << 0 << "\n";
	}
	else {
		if(search(s))
			cout << 1 << " " << C << "\n";
		else
			cout << 0 << " " << 0 << "\n";
	}
}