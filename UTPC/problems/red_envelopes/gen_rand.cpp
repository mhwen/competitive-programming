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
	int n = opt<int>("n", 2e5);
    int minA = opt<int>("minA", 1);
    int maxA = opt<int>("maxA", 1e9);
    bool evenOnly = opt<bool>("evenOnly", false);

	cout << n << "\n";
    for(int i = 0; i < n; i++) {
        int a = rnd.next(minA, maxA);
        if(evenOnly)
            a -= a%2;
        cout << a;
        if(i < n-1)
            cout << " ";
        else
            cout << "\n";
    }
}