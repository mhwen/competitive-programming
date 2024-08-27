#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MAX_N = 2e5;

char c[2] = {'U', 'D'};

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
    int nSize = atoi(argv[1]);
    int numChunks = atoi(argv[2]);
    int tests = MAX_N/nSize;
    cout << tests << "\n";
    for(int t = 0; t < tests; t++) {
        int start = rnd.next(1, 2);
        cout << nSize << "\n";
        vector<int> nums = rnd.partition(numChunks, nSize);
        for(int i = 0; i < (int)nums.size(); i++) {
            for(int j = 0; j < nums[i]; j++)
                cout << c[(i+start)%2];
        }
        cout << "\n";
    }
}