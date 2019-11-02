#include<cstdio>

const int maxn = 1e6 + 10;
int n, m, k, d;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
struct dat {
	int x, y;
};
struct qwq {
	dat q[maxn];
	int h, t;
	qwq () {h = 1, t = 0; }
	bool empty() {return h > t; }
	void push(const dat &tmp) {q[++t] = tmp; }
	void pop() {h++; }
	dat head() {return q[h]; }	
}	qaq;
int w[1010][1010], dist[1010][1010];
long long ans;
bool vis[1010][1010];

int read() {
	int a = 0;
	char ch;
	while((ch = getchar()) < 48);
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
bool check(int x, int y) {
	if(x < 1 || x > n) return 0;
	if(y < 1 || y > n) return 0;
	if(w[x][y] == -1) return 0;
	if(vis[x][y] == 1) return 0;
	return 1;
}
void bfs() {
	while(!qaq.empty()) {
		dat r = qaq.head();
		qaq.pop();
		for(int i = 0; i < 4; ++i) {
			int rx = r.x + dx[i], ry = r.y + dy[i];
			if(check(rx, ry)) {
				dist[rx][ry] = dist[r.x][r.y] + 1;
				vis[rx][ry] = 1;
				ans += 1ll * w[rx][ry] * dist[rx][ry];
				qaq.push((dat){rx, ry});
			}
		}
	}
}
int main() {
	freopen("good2.in", "r", stdin);
	freopen("good2.out", "w", stdout);
	n = read(), m = read(), k = read(), d = read();
	for(int i = 1; i <= m; ++i) {
		int x = read(), y = read();
		qaq.push((dat){x, y});
		vis[x][y] = 1; 
	}
	for(int i = 1; i <= k; ++i) {
		int x = read(), y = read(), z = read();
		w[x][y] += z;
	}
	for(int i = 1; i <= d; ++i) {
		int x = read(), y = read();
		w[x][y] = -1;
	}
	bfs();
	printf("%lld\n", ans);
	return 0;
}
