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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		if(n == 1)
			cout << 1 << "\n";
		else if(n == 3)
			cout << 169 << "\n" << 196 << "\n" << 961 << "\n";
		else {
			for(int i = 0; i < n/2; i++) {
				cout << "1";
				int first = 1+i;
				int second = 2+2*i;
				for(int id = 1; id < n; id++) {
					if(id == first)
						cout << "6";
					else if(id == second)
						cout << "9";
					else
						cout << "0";
				}
				cout << "\n";
			}
			
			cout << "61009";
			for(int i = 5; i < n; i++)
				cout << "0";
			cout << "\n";
			
			for(int i = 0; i < n/2; i++) {
				cout << "9";
				int first = 1+i;
				int second = 2+2*i;
				for(int id = 1; id < n; id++) {
					if(id == first)
						cout << "6";
					else if(id == second)
						cout << "1";
					else
						cout << "0";
				}
				cout << "\n";
			}
		}
	}
}