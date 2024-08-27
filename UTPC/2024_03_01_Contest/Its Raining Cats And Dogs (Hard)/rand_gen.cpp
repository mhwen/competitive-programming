#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MIN_INCREASE = 1;
constexpr int MAX_INCREASE = 1e5;
constexpr int MIN_HEIGHT = 0;
constexpr int MAX_HEIGHT = 1e5;
 
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    int N = atoi(argv[1]);
	int Q = atoi(argv[2]);
	cout << N << " " << Q << "\n";
	for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        cout << rnd.next(MIN_HEIGHT, MAX_HEIGHT);
    }
	cout << "\n";
	
	for(int i = 0; i < Q; i++)
		cout << rnd.next(1, N) << " " << rnd.next(MIN_INCREASE, MAX_INCREASE) << "\n";
}
