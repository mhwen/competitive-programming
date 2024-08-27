#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int c, d;
	cin >> c >> d;
	vector<int> fizz;
	vector<int> buzz;
	for(int num = c; num <= d; num++) {
		string s;
		cin >> s;
		if(s == "Fizz") {
			fizz.push_back(num);
		}
		else if(s == "Buzz") {
			buzz.push_back(num);
		}
		else if(s == "FizzBuzz") {
			fizz.push_back(num);
			buzz.push_back(num);
		}
	}
	if(sz(fizz) == 0)
		cout << d+1;
	else if(sz(fizz) == 1)
		cout << fizz.back();
	else
		cout << fizz[1]-fizz[0];
		
	cout << " ";
	if(sz(buzz) == 0)
		cout << d+2;
	else if(sz(buzz) == 1)
		cout << buzz[0];
	else
		cout << buzz[1]-buzz[0] << "\n";;
	
}