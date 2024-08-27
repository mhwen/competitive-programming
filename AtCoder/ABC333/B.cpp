#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <functional>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	string t;
	cin >> s >> t;
	int d1 = 0;
	while(s[0] != s[1]) {
		s[0]++;
		if(s[0] > 'E')
			s[0] = 'A';
		d1++;
	}
	int d2 = 0;
	while(t[0] != t[1]) {
		t[0]++;
		if(t[0] > 'E')
			t[0] = 'A';
		d2++;
	}
	if((d1==2 || d1==3) && (d2==2||d2==3))
		cout << "Yes\n";
	else if((d1==1 || d1==4) && (d2==1||d2==4))
		cout << "Yes\n";
	else
		cout << "No\n";
}