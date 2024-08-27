#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int MAX_T = 1e4;
constexpr int MAX_N = 2e5;
 
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    int N = atoi(argv[1]);
    int repeats = atoi(argv[2]);
    int period = N/repeats;
	int T = min(MAX_N/N, MAX_T);
	cout << T << "\n";
    for(int t = 0; t < T; t++) {
        cout << N << "\n";
        for(int i = 0; i < N; i++) {
            if(i > 0)
                cout << " ";
            cout << (N-i+period-1)%period+1;
        }
        cout << "\n";
    }
}
