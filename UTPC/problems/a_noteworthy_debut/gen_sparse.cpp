#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MAX_SIZE = 1e9;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int T = atoi(argv[1]);
    int N = atoi(argv[2]);
    int density = atoi(argv[3]);
    int n = N/T;
    cout << T << "\n";
    for(int t = 0; t < T; t++) {
    	cout << n << "\n";
    	for(int i = 0; i < n; i++) {
            if(i > 0)
                cout << " ";
            int num = rnd.next(1, density);
            if(num == density) {
                cout << rnd.next(2, MAX_SIZE);
            }
            else
                cout << 1;
    	}
        cout << "\n";
    }
}