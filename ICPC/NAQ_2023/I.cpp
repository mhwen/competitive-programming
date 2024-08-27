#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

typedef long long ll;

bool check(string& s, int index, int num) {
	string n = to_string(num);
	for(int i = 0; i < (int)n.length(); i++) {
		if(i+index >= (int)s.length())
			return false;
		if(s[i+index] != n[i])
			return false;
	}
	return true;
}

vector<int> check(int num, string& s) {
	int index = 0;
	int curr = num;
	bool eaten = false;
	vector<int> ans;
	while(index < (int)s.length()) {
		if(curr > 99999)
			return vector<int>();
		if(check(s, index, curr)) {
			index += (int)to_string(curr).length();
			curr++;
		}
		else {
			if(!eaten) {
				eaten = true;
				ans.push_back(curr);
				curr++;
			}
			else
				return vector<int>();
		}

	}
	if(!eaten) {
		ans.push_back(num-1);
		ans.push_back(curr);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		string s;
		cin >> s;
		set<int> ans;
		for(int i = 1; i <= min((int)s.length(), 5); i++) {
			auto res = check(stoi(s.substr(0, i)), s);
			for(int j : res) {
				if(j >= 1 && j <= 99999)
					ans.insert(j);
			}
				
		}
		cout << ans.size() << "\n";
		for(int i : ans)
			cout << i << " ";
		cout << "\n";
		
	}
}