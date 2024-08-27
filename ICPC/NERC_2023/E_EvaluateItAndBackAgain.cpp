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
	ll a, b;
	cin >> a >> b;
	ll fix = 0;
	if(abs(a%2) != abs(b%2)) {
		if(abs(a%2)==1) {
			fix = 21;
			a -= 21;
			b -= 12;
		}
		else {
			fix = 12;
			a -= 12;
			b -= 21;
		}
	}
	ll amnt = 0;
	if(abs(a%2)==1 && abs(b%2)==1) {
		amnt++;
		a--;
		b--;
	}
	while(a%10==0 || b%10==0) {
		amnt+=2;
		a -= 2;
		b -= 2;
	}
	bool aNeg = false;
	if(a < 0) {
		aNeg = true;
		a = -a;
	}
	bool bNeg = false;
	if(b < 0) {
		bNeg = true;
		b = -b;
	}
	string A = to_string(a/2);
	string aString = aNeg ? 
							"0-"+A+"-"+A+"+0+" : 
							"0+"+A+"+"+A+"-0+";
	string B = to_string(b/2);
	reverse(B.begin(), B.end());
	string bString = bNeg ? 
							"0+"+B+"-"+B+"-0" : 
							"0-"+B+"+"+B+"+0";
	cout << amnt << "+" << fix << "+" << aString << bString << "\n";
	
}