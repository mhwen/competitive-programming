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

string chars = "abcdefghijklmnopqrstuvwxyz_,.?!():;";

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	string out1 = "";
	for(int i = 0; i < (int)s.size(); i++) {
		out1 += chars[i/(int)chars.size()];
	}
	cout << out1 << endl;
	string in1;
	cin >> in1;
	string out2 = "";
	for(int i = 0; i < (int)s.size(); i++) {
		out2 += chars[i%(int)chars.size()];
	}
	cout << out2 << endl;
	string in2;
	cin >> in2;
	vector<int> perm(s.size());
	for(int i = 0; i < (int)s.size(); i++) {
		char a = out1[i];
		char b = out2[i];
		for(int j = 0; j < (int)s.size(); j++) {
			if(in1[j] == a && in2[j] == b)
				perm[j] = i;
		}
	}
	
	vector<char> ans(s.size());
	for(int i = 0; i < (int)s.size(); i++) {
		ans[perm[i]] = s[i];
	}
	for(char c : ans)
		cout << c;
	cout << endl;
	
}