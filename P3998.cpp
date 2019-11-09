#include<cstdio>
#include<algorithm>

const int MAXV = 5e5 + 10, MAXM = 2e6 + 100, MAXS = 2e5 + 10, MAXN = 1e5 + 10;
int N, R, S, X;
struct Node {
	int h[MAXV], c, nxt[MAXM], v[MAXM], w[MAXM];
	void init(int from, int to, int val) {
		v[++c] = to, w[c] = val, nxt[c] = h[from];
		h[from] = c; 
	}
}	G;
int inT[MAXV], T[MAXS], E[MAXN], C[MAXN], seq[MAXS];

int read() {
	int a = 0;
	char ch;
	while((ch = getchar()) < 48);
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
void inring() {
}
void insingle() {
}
void input() {
	N = read(), R = read(), S = read(), X = read();
	for(int i = 1; i <= N; ++i)
		G.init(i, i + N, X), G.init(i + N, i, 0);
	for(int i = 1; i <= N; ++i) {
		E[i] = read();
		G.init(i, i + 2 * N, E[i]);
	}
	for(int i = 1; i <= N; ++i)
		C[i] = read();
	for(int i = 1; i <= R; ++i) {
		int a = read(), b = read(), t = read();
		G.init(a + N, b + N, t), G.init(b + N, a + N, t);
	}
	for(int i = 1; i <= S; ++i) {
		int k = read();
		for(int j = 1; j <= 2 * k + 1; ++j)
			seq[j] = read();
		if(seq[1] == seq[2 * k + 1])
			inring();
		else
			insingle();
	}
}
int main() {
	input();
	dij();
	return 0;
}
