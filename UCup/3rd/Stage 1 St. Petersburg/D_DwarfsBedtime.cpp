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

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()

// #define LOCAL

constexpr int INF = 1e9;

string conv(int t) {
    int h = t / 60;
    int m = t % 60;

    string res;
    if( h == 24 ) h = 0;
    if (h < 10) res += "0";
    res += to_string(h);
    res += ":";
    if (m < 10) res += "0";
    res += to_string(m);

    return res;
}

int convt(string s) {
    auto h = stoi(s.substr(0, 2));
    auto m = stoi(s.substr(3, 2));
    return h*60 + m;
}

#ifdef LOCAL

int start_t[1440];

int last_t;
int asked[1440]; // dont ask for more
bool sleeping(int t, int loc) {
    cout << "at " << conv(t) << " check " << loc+1 << endl;
    
    auto start = start_t[loc];
    asked[loc]++;

    if (last_t > t) {
        cout << "!!! going backwards !!!" << endl;
    }
    last_t = t;

    int end = start + 720;
    if (end > 1440) {
        end -= 1440;
        return t < end || t >= start;
    } else {
        return t >= start && t < end;
    }
}

#else

bool sleeping(int t, int loc) {
    cout << "at " << conv(t) << " check " << loc+1 << endl;
    string res;
    cin >> res;
    return res == "asleep";
}

#endif

void answer(const vector<int> &t) {
    cout << "answer\n";
    for (auto x : t) {
        cout << conv(x) << endl;
    }

#ifdef LOCAL
    if (any_of(begin(asked), end(asked), [](int x) { return x > 50; })) {
        cout << "!!!too many queries!!!!\n";
    }
#endif
}

int main() {
	
	#ifdef LOCAL
	iota(begin(start_t), end(start_t), 1200);
	#endif
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//min moves for x floors and y eggs
	vector<vector<int>> dp(721, vector<int>(2, INF));
	dp[0][0] = 0;
	vector<int> split(721);
	for(int i = 1; i < sz(dp); i++)
		dp[i][0] = i;
	dp[0][1] = 0;
	for(int i = 0; i < sz(dp); i++) {
		//splitting point
		//drop at jth floor
		for(int j = 1; j <= i; j++) {
			int die = dp[j-1][0];
			int live = dp[i-j][1];
			int score = max(die, live)+1;
			if(score <= dp[i][1]) {
				dp[i][1] = score;
				split[i] = j;
			}
		}
		// cout << i << " floors, split at " << split[i] << " and takes " << dp[i][1] << endl;
	}
	
	int n;
	cin >> n;
	
	//first query 0
	//want to find +x where border is
	//after first egg breaks, want to find 720+x
	
	//query -> same = egg live
	//query -> diff = egg die
	
	//to handle multiple guys, keep a priority queue of queries by time
	//{time, id}
	priority_queue<pair<int, int>> q;
	
	//[minFloor, maxFloor] is candidate range for beginning of interval 
	//(i.e. lowest floor egg breaks on)
	//(i.e. the +x value we want to find)
	vector<int> minFloor(n, 1);
	vector<int> maxFloor(n, 720);
	vector<bool> secondEgg(n, false);
	vector<bool> startedSleeping(n);
	for(int i = 0; i < n; i++) {
		startedSleeping[i] = sleeping(0, i);
	}
	
	vector<int> ans(n);
	
	auto query = [&](int guy, bool schedule) {
		int floors = maxFloor[guy]-minFloor[guy];
		
		//found the answer, no more queries needed
		if(floors == 0) {
			if(startedSleeping[guy])
				ans[guy] = minFloor[guy]+720;
			else
				ans[guy] = minFloor[guy];
			return;
		}
		
		//get floor to query from egg drop
		int floor; 
		
		//one egg left
		if(secondEgg[guy]) {
			floor = minFloor[guy];
		}
		//two eggs still
		else {
			//split[floor] = which floor to drop egg on
			//with floor floors and 2 eggs left (1-indexed)
			int floorsFromMin = split[floors]-1;
			floor = floorsFromMin+minFloor[guy];
		}
		
		int time = floor;
		if(secondEgg[guy])
			time += 720;
		
		//schedule query
		if(schedule) {
			q.push({-time, guy});
		}
		//do query
		else {
			bool asleep = sleeping(time, guy);
			if(secondEgg[guy]) {
				//state changed (egg broke)
				if(asleep == startedSleeping[guy]) {
					maxFloor[guy] = floor;
				}
				//remained same (egg lived)
				else {
					minFloor[guy] = floor+1;
				}
			}
			else {
				//state changed (egg broke)
				if(asleep != startedSleeping[guy]) {
					maxFloor[guy] = floor;
					secondEgg[guy] = true;
				}
				//remained same (egg lived)
				else {
					minFloor[guy] = floor+1;
				}
			}
		}
	};
	
	//schedule first query for each guy
	for(int i = 0; i < n; i++) {
		query(i, true);
	}
	
	while(!q.empty()) {
		auto [time, guy] = q.top();
		q.pop();
		//do current query
		query(guy, false);
		//schedule next one
		query(guy, true);
	}
	
	answer(ans);
	// cout << "answer" << endl;
	// for(int i = 0; i < n; i++) {
		// cout << conv(ans[i]) << endl;
	// }
	
}