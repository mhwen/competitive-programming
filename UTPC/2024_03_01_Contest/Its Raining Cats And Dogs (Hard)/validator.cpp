#include "testlib.h"
 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constexpr int MAX_N = 1e5;
constexpr int MAX_Q = 1e5;
constexpr int MIN_HEIGHT = 0;
constexpr int MAX_HEIGHT = 1e5;
constexpr int MIN_INCREASE = 1;
constexpr int MAX_INCREASE = 1e5;
 
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int N = inf.readInt(1, MAX_N, "N");
	inf.readSpace();
	int Q = inf.readInt(1, MAX_Q, "Q");
	inf.readEoln();
    
	for (int i = 0; i < N; i++) {
		int h = inf.readInt(MIN_HEIGHT, MAX_HEIGHT, "h_i");
        if(i < N-1)
	        inf.readSpace();
        else
            inf.readEoln();
	}
	for (int i = 0; i < Q; i++) {
		int p = inf.readInt(1, N, "p_i");
        inf.readSpace();
        int x = inf.readInt(MIN_INCREASE, MAX_INCREASE, "x_i");
		inf.readEoln();
	}
    inf.readEof();
}