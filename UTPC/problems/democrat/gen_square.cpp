#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int n = opt<int>("n", 2e3);
    int r = opt<int>("r", 1e6);
	cout << n << " " << r << "\n";
    int s = (int)sqrt(n)+1;
    int offsetx = rnd.next(-10000, 10000);
    int offsety = rnd.next(-10000, 10000);
    for(int i = 0; i < n; i++) {
        cout << i/s+offsetx << " " << i%s+offsety << "\n";
    }
}