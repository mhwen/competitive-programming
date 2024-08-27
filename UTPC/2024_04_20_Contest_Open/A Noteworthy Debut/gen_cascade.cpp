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
    int N = atoi(argv[1]);
    cout << 1 << "\n";
    cout << N << "\n";
    int pow = 0;
    for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        cout << (1<<pow);
        pow = (pow+1)%30;
    }
    cout << "\n";
}