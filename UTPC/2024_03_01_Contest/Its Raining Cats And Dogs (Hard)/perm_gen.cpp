#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MAX_INCREASE = 1e5;
 
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
 
    int N = atoi(argv[1]);
	int Q = N;
	cout << N << " " << Q << "\n";
    vector<int> permutation = rnd.perm(N);
    vector<int> locs(N);
	for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        cout << permutation[i];
        locs[permutation[i]] = i;
    }
	cout << "\n";
	
	for(int i = 0; i < Q; i++)
		cout << locs[i]+1 << " " << MAX_INCREASE << "\n";
}
