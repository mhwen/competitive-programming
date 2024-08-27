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
 
struct Node {
	Node* next[26];
	
	Node() {
		for(int i = 0; i < 26; i++) {
			next[i] = nullptr;
		}
	}
 
};
 
array<vector<int>, 2> manacher(string& s) {
	int n = (int)s.length();
	array<vector<int>, 2>p = {vector<int>(n+1), vector<int>(n)};
	for(int z = 0; z < 2; z++) {
		for(int i=0,l=0,r=0; i < n; i++) {
			int t = r-i+!z;
			if(i<r) p[z][i] = min(t, p[z][l+t]);
			int L = i-p[z][i], R = i+p[z][i]-!z;
			while (L>=1 && R+1<n && s[L-1] == s[R+1])
				p[z][i]++, L--, R++;
			if(R>r) l=L, r=R;
		}
	}
	return p;
}
 
 
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	string s;
	cin >> n >> s;
	map<char, int> seen;
	vector<int> left(n);
	for(int i = 0; i < n; i++) {
		for(auto c : seen) {
			if(c.first == s[i])
				continue;
			left[i] = max(left[i], c.second);
		}
		seen[s[i]] = i;
	}
	if((int)seen.size() == 1) {
		cout << (seen.begin()->first-'a'+1)*((ll)n)*(n+1)/2 << "\n";
		return 0;
	}
	auto pal = manacher(s);
	vector<Node*> odds(26);
	Node* even = new Node();
	
	function<void(Node*, int, int)> insert = [&](Node* root, int l, int r) {
		Node* curr = root;
		for(int i = l; i < r; i++) {
			int c = s[i]-'a';
			if(curr->next[c] == nullptr) {
				curr->next[c] = new Node();
			}
			curr = curr->next[c];
		}
	};
	
	function<void(int)> process = [&](int i) {
		
		bool doEven = true;
		bool doOdd = true;
		
		if(i > 0) {
			if(pal[0][i] <= pal[0][i-1]-1)
				doEven = false;
			if(i-left[i] >= 5 && pal[1][i] <= pal[1][i-1]-1)
				doOdd = false;
		}
		if(i < n-1) {
			if(pal[0][i] <= pal[0][i+1]-1)
				doEven = false;
			if(i-left[i] >= 5 && pal[1][i] <= pal[1][i+1]-1)
				doOdd = false;
		}
		
		if(doEven)
			insert(even, i, i+pal[0][i]);
		
		if(doOdd) {
			if(odds[s[i]-'a'] == nullptr)
				odds[s[i]-'a'] = new Node();
			insert(odds[s[i]-'a'], i+1, i+1+pal[1][i]);
		}
	};
	
	for(int i = 0; i < n; i++) {
		process(i);
	}
	
	ll ans = 0;
	
	function<void(Node*, ll)> count = [&](Node* curr, ll amt) {
		ans += amt;
		for(int i = 0; i < 26; i++) {
			if(curr->next[i] != nullptr) {
				count(curr->next[i], amt+2*(i+1));
			}
		}
	};
	
	count(even, 0);
	for(int i = 0; i < 26; i++) {
		if(odds[i] != nullptr)
			count(odds[i], i+1);
	}
	
	cout << ans << "\n";
}
