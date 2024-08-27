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
    int sampleSize = atoi(argv[3]);
    int chance = atoi(argv[4]);
	cout << N << " " << Q << "\n";
	for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        cout << rnd.next(MIN_HEIGHT, MAX_HEIGHT);
    }
	cout << "\n";

    vector<int> samples;
    set<int> seen;
	for(int i = 0; i < sampleSize; i++) {
        int pos = rnd.next(1, N);
        while(seen.count(pos)) {
            pos = rnd.next(1, N);
        }
        seen.insert(pos);
        samples.push_back(pos);
    }
	
	for(int i = 0; i < Q; i++) {
        int which = rnd.next(1, 100);
        if(which <= chance) {
            int p = samples[rnd.next((int)samples.size())];
            cout << p << " " << rnd.next(MIN_INCREASE, MAX_INCREASE) << "\n";
        }
        else {
            cout << rnd.next(1, N) << " " << rnd.next(MIN_INCREASE, MAX_INCREASE) << "\n";
        }
    }
		
}
