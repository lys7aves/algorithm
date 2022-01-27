#include <stdio.h>
#include <set>
#include <queue>
#include <stack>
#include <map>

#define MAXN 129140163

using namespace std;

int n;
map<long long, long long> Prev;
int where[26], cnt[3];
queue<long long> que;
stack<int> st;

int s[6] = { 0,0,1,1,2,2 };
int e[6] = { 1,2,0,2,0,1 };

int move(long long state, int x, int y);
void printState(char* str, long long state);

int main()
{
	long long state = 0, goal = 0, state_;
	int i;

//	freopen_s("output.txt", "w", stdout);

	//	for(n=1; n<=10; n++){
	//		state = goal = 0;

	n = 26;

	for (i = 0; i < n; i++) {
		goal *= 3;
		goal += 2;
	}
	//	printf("goal : %d\n", goal);

	while (!que.empty()) que.pop();

	Prev[state] = (long long)0;
	que.push(state);
	while (!que.empty()) {
		state = que.front();
		que.pop();

		/*		printf("      ");
				for(i=0; i<n; i++) printf("%d ", i);
				printf("\n");
				printState("Prev: ", Prev[state]);
				printState("stat: ", state);*/

		if (state == goal) break;

		for (i = 0; i < 6; i++) {
			state_ = move(state, s[i], e[i]);
			/*			printf("%d->%d: ", s[i], e[i]);
						printState("", state_);*/

			if (state_ == -1) continue;
			if (Prev.find(state_) != Prev.end()) continue;
			Prev[state_] = state * 6 + i;
			que.push(state_);
		}

		//		printf("\n");
	}

	state = goal;
	while (state > 0) {
		st.push(Prev[state] % 6);
		state = Prev[state] / 6;
	}

	printf("%2d\n", n);
	while (!st.empty()) {
		printf("%c", st.top() + 'A');
		st.pop();
	}
	printf("\n");

	return 0;
}

int move(long long state, int x, int y)
{
	int i, xcnt, ycnt, xnum;

	cnt[0] = cnt[1] = cnt[2] = 0;
	for (i = 0; i < n; i++) {
		where[i] = state % 3;
		cnt[where[i]]++;
		state /= 3;
	}

	if (cnt[x] == 0) return -1;

	xcnt = cnt[x] / 2 + 1;
	ycnt = (cnt[y] + 1) / 2 + 1;

	for (i = 0; i < n; i++) {
		if (where[i] == x) xcnt--;

		if (xcnt == 0) {
			xnum = i;
			break;
		}
	}

	for (i = 0; i < n; i++) {
		if (where[i] == y) {
			ycnt--;
			if (ycnt == 0) {
				if (xnum < i) i = n;
				break;
			}
			if (xnum < i) break;
		}
	}
	if (i < n) return -1;

	where[xnum] = y;

	state = 0;
	for (i = n - 1; i >= 0; i--) {
		state *= 3;
		state += where[i];
	}

	return state;
}

void printState(char* str, long long state)
{
	printf("%s", str);

	if (state == -1) {
		printf("-1\n");
		return;
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", state % 3);
		state /= 3;
	}
	printf("\n");
}
