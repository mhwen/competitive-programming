#include "testlib.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr int LEN = 1e6;

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	registerGen(argc, argv, 1);
	int M = atoi(argv[1]);
	int mid = rnd.next(2, LEN-1);
	cout << 1 << " " << M << "\n";
	cout << mid << "\n";
	int count = 0;
	while(count < M) {
		int left = rnd.next(1, LEN);
		int right = rnd.next(1, LEN);
		if(left > right)
			swap(left, right);
		if(left <= mid && mid <= right)
			continue;
		cout << left << " " << right << " " << count+1 << "\n";
		count++;
	}
}