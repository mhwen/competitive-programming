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
    int type = atoi(argv[2]);
	cout << N << " " << Q << "\n";

    int start = 0;
    if(type == -1)
        start = N-1;

	for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        cout << start + i*type;
    }
	cout << "\n";
	
	for(int i = 0; i < Q; i++)
		cout << start+1+i*type << " " << MAX_INCREASE << "\n";
}
