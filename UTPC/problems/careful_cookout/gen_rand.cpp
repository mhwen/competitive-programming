#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int MIN_SIZE = 2;
constexpr int MAX_SIZE = 2000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(MIN_SIZE, MAX_SIZE);
    int M = rnd.next(MIN_SIZE, MAX_SIZE);
    cout << N << " " << M << "\n";
}