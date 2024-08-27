#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int inputs;
	cin >> inputs;
	vector<int> chars(26);
	while(inputs-->0) {
		fill(chars.begin(), chars.end(), 0);
		string s;
		cin >> s;
		for(char c : s) {
			chars[c-'a']++;
		}
		int n = s.length();
		string a = "";
		string b = "";
		int index = 0;
		deque<char> extras;
		for(int i = 0; i < n/2; i++) {
			while(chars[index] < 2) {
				if(chars[index] == 1) {
					extras.push_back((char)(index+'a'));
				}
				index++;
			}
			if(extras.size() >= 2) {
				char first = extras.front();
				extras.pop_front();
				char second = extras.front();
				extras.pop_front();
				a += first;
				b += second;
				chars[first-'a']--;
				chars[second-'a']--;
				break;
			}
			if(extras.size() == 1) {
				int next = index+1;
				while(next < 26 && chars[next] == 0) {
					next++;
				}
				if(next != 26) {
					char first = extras.front();
					extras.pop_front();
					char second = (char)(index+'a');
					a += first;
					b += second;
					b += second;
					chars[first-'a']--;
					chars[second-'a']-=2;
					break;
				}

			}
			char cc = (char)(index+'a');
			chars[index]-=2;
			a += cc;
			b += cc;

		}
		index = 0;
		while((int)(b.length()+a.length()) < n) {
			while(chars[index] == 0)
				index++;
			char ch = (char)(index+'a');
			chars[index]--;
			b += ch;
		}
		reverse(a.begin(), a.end());
		cout << b << a << "\n";
	}
}