#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int LEN = 1e6;
constexpr int MAX_HEIGHT = 1e9;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
	cout << N << " " << M << "\n";

    set<int> molds;
	for(int i = 0; i < N; i++) {
        if(i > 0)
            cout << " ";
        int moldPos = rnd.next(1, LEN);
        while(molds.count(moldPos)) {
            moldPos = rnd.next(1, LEN);
        }
        cout << moldPos;
        molds.insert(moldPos);
    }
    cout << "\n";

    set<int> heights;
    for(int i = 0; i < M; i++) {
        int left = rnd.next(1, LEN);
		int right = rnd.next(1, LEN);
		if(left > right)
			swap(left, right);
        int height = rnd.next(1, MAX_HEIGHT);
        while(heights.count(height)) {
            height = rnd.next(1, MAX_HEIGHT);
        }
        cout << left << " " << right << " " << height << "\n";
        heights.insert(height);
    }
}