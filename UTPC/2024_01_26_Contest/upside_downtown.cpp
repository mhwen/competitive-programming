#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <regex>

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	cin >> s;
	if(regex_match(s, regex("[1689]([01689]*[1689])?")))
		cout << "YES\n";
	else
		cout << "NO\n";
}