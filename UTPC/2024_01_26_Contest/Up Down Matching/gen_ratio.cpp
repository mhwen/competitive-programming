#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MAX_N = 2e5;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
    int nSize = atoi(argv[1]);
    int Uratio = atoi(argv[2]);
    int Dratio = atoi(argv[3]);
    int tests = MAX_N/nSize;
    cout << tests << "\n";
    for(int t = 0; t < tests; t++) {
        cout << nSize << "\n";
        for(int i = 0; i < nSize; i++) {
            int res = rnd.next(1, Uratio+Dratio);
            if(res <= Uratio)
                cout << "U";
            else
                cout << "D";
        }
        cout << "\n";
    }

}