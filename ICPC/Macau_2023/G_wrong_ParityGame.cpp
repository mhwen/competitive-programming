#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>

using namespace std;

typedef long long ll;

vector<int> process(vector<int>& num, char op, int id) {
	id--;
	vector<int> newNum;
	for(int i = 0; i < id; i++) {
		newNum.push_back(num[i]);
	}
	
	int val = (num[id]+num[id+1])%2;
	if(op == '*')
		val = num[id]*num[id+1]%2;
	newNum.push_back(val);
	for(int i = id+2; i < (int)num.size(); i++)
		newNum.push_back(num[i]);
	return newNum;
}

vector<int> processOpponent(vector<int>& nums) {
	int id;
	char op;
	cin >> id >> op;
	return process(nums, op, id);
}

vector<int> doMove(vector<int>& num, char op, int id) {
	cout << id << " " << op << endl;
	return process(num, '+', id);
}

vector<int> killOdd(vector<int>& num) {
	//oo
	for(int i = 0; i < (int)num.size()-1; i++) {
		if(num[i]%2==1 && num[i+1]%2==1) {
			return doMove(num, '+', i+1);
		}
	}
	//eo
	if(num.back()%2==1) {
		return doMove(num, '*', (int)num.size()-1);
	}
	//oe
	for(int i = 0; i < (int)num.size()-1; i++) {
		if(num[i]%2==1) {
			return doMove(num, '*', i+1);
		}
	}
	//ee
	return doMove(num, '+', 1);
}

int countOdds(vector<int>& num) {
	int oddPairs = 0;
	int oddSingles = 0;
	int n = (int)num.size();
	for(int i = 0; i < (int)num.size(); i++) {
		if(num[i]%2==0)
			continue;
		if(i < n-1 && num[i+1]%2==1) {
			oddPairs++;
			i++;
		}
		else
			oddSingles++;
	}
	return oddPairs+oddSingles;
}


vector<int> killEven(vector<int>& num) {
	int odds = countOdds(num);
	for(int i = 0; i < (int)num.size()-1; i++) {
		auto newNum = process(num, '+', i+1);
		int newOdds = countOdds(newNum);
		if(newOdds >= odds) {
			return doMove(num, '+', i+1);
		}
	}
	//oo
	return doMove(num, '*', 1);
}

//fails on ee
void forceOdd(vector<int>& nums) {
	if(nums[0] != nums[1])
		doMove(nums, '+', 1);
	else
		doMove(nums, '*', 1);
}

void forceEven(vector<int>& nums) {
	if(nums[0] != nums[1])
		doMove(nums, '*', 1);
	else
		doMove(nums, '+', 1);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, t;
	cin >> n >> t;
	vector<int> nums(n);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	
	int odds = countOdds(nums);
	
	if(t==0) {
		//Alice is last move
		if(n%2==0) {
			cout << "Alice" << endl;
			while((int)nums.size() > 2) {
				//my move
				nums = doMove(nums, '+', 1);
				
				//bob move
				nums = processOpponent(nums);
			}
			//i win
			forceEven(nums);
		}
		//Bob is last move
		else {
			//need last two to be even for Alice to win
			//Alice wants to kill all odds
			//n odd
			int aliceMoves = (n-1)/2;
			
			//Alice can kill all odds
			if(odds <= aliceMoves) {
				cout << "Alice" << endl;
				while((int)nums.size() > 2) {
					//my move
					nums = killOdd(nums);
					//bob move
					nums = processOpponent(nums);
				}
			}
			//Alice can't
			else {
				cout << "Bob" << endl;
				//alice move
				nums = processOpponent(nums);
				while((int)nums.size() > 2) {
					//my move
					nums = killEven(nums);
					//alice move
					nums = processOpponent(nums);
				}
				forceOdd(nums);
			}
		}
	}
	else {
		//Bob is last move
		if(n%2==1) {
			cout << "Bob" << endl;
			//alice move
			nums = processOpponent(nums);
			while((int)nums.size() > 2) {
				//my move
				nums = doMove(nums, '+', 1);
				
				//alice move
				nums = processOpponent(nums);
			}
			//i win
			forceEven(nums);
		}
		//Alice is last move
		else {
			//need last two to have an odd for Alice to win
			//Bob wants to kill odds
			//n even
			int bobMoves = (n-2)/2;
			//Bob can kill all odds
			if(odds <= bobMoves) {
				cout << "Bob" << endl;
				//alice move
				nums = processOpponent(nums);
				while((int)nums.size() > 2) {
					//my move
					nums = killOdd(nums);
					//alice move
					nums = processOpponent(nums);
				}
			}
			//Bob can't
			else {
				cout << "Alice" << endl;
				while((int)nums.size() > 2) {
					//my move
					nums = killEven(nums);
					//bob move
					nums = processOpponent(nums);
				}
				forceOdd(nums);
			}
		}
	}
}