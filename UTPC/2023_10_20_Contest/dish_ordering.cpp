#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	string s1;
	cin >> s1;
	string s2; 
	cin >> s2;
	int swaps = 0;
	bool good = true;
	for(int i = 0; i < n; i++) {
		bool found = false;
		for(int j = i; j < n; j++) {
			if(s1[i] == s2[j]) {
				found = true;
				while(j > i) {
					swap(s2[j], s2[j-1]);
					swaps++;
					j--;
				}
				break;
			}		
		}
		if(!found)
			good = false;
	}
	if(good)
		cout << swaps << "\n";
	else
		cout << -1 << "\n";
}