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

void read(string a) {
	cout << "yoink " << a << "\n";
}

//a := a+b
void add(string a, string b) {
	cout << "*slaps " << b << " on top of " << a << "*\n";
}

void print(string a) {
	cout << "yeet " << a << "\n";
}

void exit() {
	cout << "go touch some grass\n";
}

void setVar(string a, string val) {
	cout << "bruh " << a << " is lowkey just " << val << "\n";
}

//a := a-b
void subtract(string a, string b) {
	cout << "rip this " << a << " fell off by " << b << "\n";
}

//check if a > b
void compare(string a, string b) {
	cout << "vibe check " << a << " ratios " << b << "\n";
}

void jumpTo(int line) {
	cout << "simp for " << line << "\n";
}

void swap(string a, string b) {
	setVar("h", a);
	setVar(a, b);
	setVar(b, "h");
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int x;
	cin >> x;
	if(x == 1) {
		read("a");
		read("b");
		add("a", "b");
		print("a");
		exit();
	}
	else if(x == 2) {
		read("a");
		setVar("b", "0");
		subtract("b", "a");
		compare("a", "b");
		jumpTo(7);
		setVar("a", "b");
		print("a");
		exit();
	}
	else if(x == 3) {
		read("n");
		read("a");
		setVar("m", "a[0]");
		setVar("i", "1");
		compare("n", "i");
		jumpTo(9);
		print("m");
		exit();
		compare("a[i]", "m");
		setVar("m", "a[i]");
		add("i", "1");
		jumpTo(5);
	}
	else {
		read("n");
		read("a");
		read("k");
		subtract("n", "1");
		setVar("i", "0");
			compare("i", "n"); //6
			jumpTo(20);
			setVar("j", "i");
				compare("j", "n"); //9
				jumpTo(18);
				compare("a[i]", "a[j]");
				jumpTo(16);
				swap("a[j]", "a[i]");
				add("j", "1"); //16
				jumpTo(9);
			add("i", "1"); //18
			jumpTo(6);
		subtract("k", "1"); //20
		print("a[k]");
		exit();
	}
}