#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

struct Node {
	map<int, Node*> next;
	int count;
	Node() : count(0) {}
};

int query(Node* start, string s) {
	Node* curr = start;
	for(char c : s) {
		int val = c-'a';
		if(curr->next[val] == NULL)
			return 0;
		curr = curr->next[val];
	}
	return curr->count;
}

int query2(Node* start, string pre, string suf) {
	Node* curr = start;
	for(int i = 0; i < (int)pre.length(); i++) {
		int left = pre[i]-'a';
		int right = suf[i]-'a';
		int val = left*26+right;
		if(curr->next[val] == NULL)
			return 0;
		curr = curr->next[val];
	}
	return curr->count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Node* prefix = new Node();
	Node* suffix = new Node();
	Node* both = new Node();
	int n, q;
	cin >> n >> q;
	for(int j = 0; j < n; j++) {
		string s;
		cin >> s;
		Node* currP = prefix;
		Node* currS = suffix;
		Node* currB = both;
		for(int i = 0; i < (int)s.length(); i++) {
			int left = s[i]-'a';
			int right = s[(int)s.length()-i-1]-'a';
			if(currP->next[left] == NULL)
				currP->next[left] = new Node();
			currP = currP->next[left];
			currP->count++;
			if(currS->next[right] == NULL)
				currS->next[right] = new Node();
			currS = currS->next[right];
			currS->count++;
			int together = left*26+right;
			if(currB->next[together] == NULL)
				currB->next[together] = new Node();
			currB = currB->next[together];
			currB->count++;
		}
	}
	while(q-->0) {
		string type;
		string a, b;
		cin >> type >> a >> b;
		reverse(b.begin(), b.end());
		if(type == "AND") {
			cout << query2(both, a, b) << "\n";
		}
		else if(type == "OR") {
			cout << query(prefix, a)+query(suffix, b)-query2(both, a, b) << "\n";
		}
		else {
			cout << query(prefix, a)+query(suffix, b)-2*query2(both, a, b) << "\n";
		}
	}
}