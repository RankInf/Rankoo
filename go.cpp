#include<cstdio>
#include<cstring>

int n, m, T;
int mp[25][25], in[25][25], cnt_p[10], cnt_c[10], tot, dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int book[25][25];
bool cur = 1, vis[25][25];
struct Q {
	int x, y;
}	q[466], last[25][25];
int h = 1, t = 0;

bool check(int x, int y) {
	if(x <= 0 || x > n) return 0;
	if(y <= 0 || y > n) return 0;
	if(vis[x][y] || mp[x][y] != (cur ^ 1)) return 0;
	return 1;
}
void bfs(int x, int y) {
	h = 1, t = 0;
	q[++t] = (Q){x, y};
	vis[x][y] = 1;
	while(h <= t) {
		Q f = q[h++];
		in[f.x][f.y] = tot;
		cnt_c[tot]++;
		for(int i = 0; i < 4; ++i) {
			int x1 = f.x + dx[i], y1 = f.y + dy[i];
			if(!check(x1, y1)) {
				if(x1 && x1 <= n && y1 && y1 <= n && mp[x1][y1] == -1 && book[x1][y1] < tot)
					book[x1][y1] = tot, cnt_p[tot]++;
				continue;
			}
			q[++t] = (Q){x1, y1}, vis[x1][y1] = 1;
		}
	}
}
void del() {
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(in[i][j] == tot)
				mp[i][j] = -1;
}
void cp(int x, int y) {
	h = 1, t = 0;
	q[++t] = (Q){x, y};
	vis[x][y] = 1;
	while(h <= t) {
		Q f = q[h++];
		for(int i = 0; i < 4; ++i) {
			int x1 = f.x + dx[i], y1 = f.y + dy[i];
			if(x1 <= 0 || x1 > n || y1 <= 0 || y1 > n || vis[x1][y1] || mp[x1][y1] != cur) {
				if(x1 && x1 <= n && y1 && y1 <= n && book[x1][y1] < tot && mp[x1][y1] == -1)
					book[x1][y1] = tot, cnt_p[tot]++;
				continue;
			}
			q[++t] = (Q){x1, y1}, vis[x1][y1] = 1;
		}
	}
}
bool judg(int x, int y) {
	tot = 0;
	memset(vis, 0, sizeof(vis));
	memset(in, 0, sizeof(in));
	memset(book, 0, sizeof(book));
	memset(cnt_p, 0, sizeof(cnt_p));
	memset(cnt_c, 0, sizeof(cnt_c));
	mp[x][y] = cur;
	bool kill = 0;
	for(int i = 0; i < 4; ++i) {
		int x1 = x + dx[i], y1 = y + dy[i];
		if(!check(x1, y1))
			continue;
		tot++;
		bfs(x1, y1);
		if(cnt_c[tot] == 1 && cnt_p[tot] == 0)
			if(last[x][y].x == x1 && last[x][y].y == y1) {
				mp[x][y] = -1;
				return 0;
			}
		if(cnt_p[tot] == 0) {
			kill = 1;
			del();
			if(cnt_c[tot] == 1)
				last[x1][y1].x = x, last[x1][y1].y = y;
		}
	}
	if(!kill) {
		tot++;
		cp(x, y);
		if(cnt_p[tot] == 0) {
			mp[x][y] = -1;
			return 0;
		}
	}
	return 1;
}
int main() {
	freopen("go.in", "r", stdin);
	freopen("go.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			mp[i][j] = -1;
	if(!m) {
		scanf("%d", &T);
		return 0;
	}
	while(m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(~mp[x][y]) {
			putchar('F');
			continue;
		}
		if(judg(x, y))
			putchar('S'), cur ^= 1;
		else
			putchar('F');
		/*for(int i = 1; i <= n; ++i, puts(""))
			for(int j = 1; j <= n; ++j)
				if(~mp[i][j])
					putchar(mp[i][j] ? 'x' : 'o');
				else
					putchar('.');
		puts("");*/
	}
	puts("");
	scanf("%d", &T);
	for(int i = 1; i <= n; ++i, puts(""))
		for(int j = 1; j <= n; ++j)
			if(~mp[i][j])
				putchar(mp[i][j] ? 'x' : 'o');
			else
				putchar('.');
	return 0;
}
