#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int packets = 0;

void send_packet(vector<bool> A) {
	packets++;
}

void send_message(vector<bool> M, vector<bool> C) {
	int first = 0;
	while(C[first])
		first++;
		
	vector<bool> allZeros(31, 0);
	vector<bool> allOnes(31, 1);
	
	for(int bit = 0; bit < 4; bit++) {
		if(first&(1<<bit))
			send_packet(allOnes);
		else
			send_packet(allZeros);
	}
	
	vector<bool> lengthVector(10);
	int len = sz(M)-1;
	for(int bit = 0; bit < 10; bit++) {
		if(len&(1<<bit))
			lengthVector[bit] = 1;
	}
	
	M.insert(M.begin(), all(lengthVector));
	
	int index = 0;
	auto sendNext = [&](bool use, bool val) {
		vector<bool> m(31);
		for(int i = 0; i < 31; i++) {
			if(C[i])
				continue;
			if(i == first && use)
				m[i] = val;
			else if(index < sz(M))
				m[i] = M[index++];
		}
		send_packet(m);
	};
	
	for(int i = 0; i < 31; i++) {
		if(i == first)
			continue;
		sendNext(true, C[i]);
	}
	while(index < sz(M))
		sendNext(false, false);
}

vector<bool> receive_message(vector<vector<bool>> messages) {
	int first = 0;
	for(int bit = 0; bit < 4; bit++) {
		int cnt = accumulate(all(messages[bit]), 0);
		if(cnt >= 16)
			first |= (1<<bit);
	}
	messages.erase(messages.begin(), messages.begin()+4);
	
	vector<bool> recovered;
	vector<bool> C(31);
	for(int i = 0; i < first; i++)
		C[i] = messages[i][first];
	C[first] = 0;
	for(int i = first+1; i < 31; i++)
		C[i] = messages[i-1][first];

	auto recover = [&](int i, bool skipFirst) {
		for(int j = 0; j < 31; j++) {
			if(C[j])
				continue;
			if(j == first && skipFirst)
				continue;
			recovered.push_back(messages[i][j]);
		}
	};
	for(int i = 0; i < 30; i++) {
		recover(i, true);
	}
	for(int i = 30; i < sz(messages); i++)
		recover(i, false);

	int messageLen = 0;
	for(int bit = 0; bit < 10; bit++) {
		if(recovered[bit])
			messageLen |= (1<<bit);
	}
	messageLen++;
	vector<bool> ans;
	for(int i = 0; i < messageLen; i++) {
		ans.push_back(recovered[i+10]);
	}
	return ans;
}

int main() {
	vector<bool> message(1024, 1);
	vector<bool> c(31);
	for(int i = 0; i < 15; i++)
		c[i] = 1;
	send_message(message, c);
	cout << packets << endl;
}