#include<cstdio>
#include<algorithm>
#include<bitset>
using namespace std;

typedef long long ll;
const int maxn = 33333, maxm = 666666;
const ll inf = 1ll << 60;
int n, m;
struct Node {
	int u, v, next;
	ll w;
}	edge[maxm << 1];
int head[maxn], cnt = 0;
struct node {
	int idx;
	ll dis;
	bool operator <(const node &tmp)const {
		return dis > tmp.dis;
	}
};
struct Heap {
	node q[maxn + maxm << 1];
	int siz;
	bool empty() {return siz == 0; }
	void push(const node &tmp) {
		q[++siz] = tmp;
		push_heap(q + 1, q + siz + 1);
	}
	void pop() {
		push_heap(q + 1, q + siz + 1);
		siz--;
	}
	node top() {return q[1]; }
}	H;
ll dis1[maxn], dis2[maxn], ans = 0;
bool vis[maxn];
int deg[maxn];
struct Graph {
	int v, next;
}	G[maxm];
int first[maxn], tot = 0;
bitset <30010> f[30010];

int read() {
	int a = 0;
	char ch;
	while((ch = getchar()) < 48);
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
void init(int u, int v, ll w) {
	edge[++cnt] = (Node){u, v, head[u], w};
	head[u] = cnt;
}
void d1() {
	for(int i = 1; i <= n; ++i)
		dis1[i] = inf;
	dis1[1] = 0;
	H.push((node){1, 0});
	while(!H.empty()) {
		node temp = H.top();
		H.pop();
		int from = temp.idx;
		if(temp.dis != dis1[from])
			continue;
		for(int k = head[from]; k; k = edge[k].next) {
			int to = edge[k].v;
			ll val = edge[k].w;
			if(dis1[to] > dis1[from] + val) {
				dis1[to] = dis1[from] + val;
				H.push((node){to, dis1[to]});
			}
		}
	}
}
void d2() {
	for(int i = 1; i <= n; ++i)
		dis2[i] = inf;
	dis2[n] = 0;
	H.push((node){n, 0});
	while(!H.empty()) {
		node temp = H.top();
		H.pop();
		int from = temp.idx;
		if(temp.dis != dis2[from])
			continue;
		for(int k = head[from]; k; k = edge[k].next) {
			int to = edge[k].v;
			ll val = edge[k].w;
			if(dis2[to] > dis2[from] + val) {
				dis2[to] = dis2[from] + val;
				H.push((node){to, dis2[to]});
			}
		}
	}
}
void link(int u, int v) {
	G[++tot] = (Graph){v, first[u]};
	first[u] = tot;
}
void dp(int x) {
	vis[x] = 1;
	for(int k = first[x]; k; k = G[k].next) {
		int to = G[k].v;
		if(!vis[to])
			dp(to);
		f[x] |= f[to];
	}
	ans += (ll)f[x].count();
	f[x][x] = 1;
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) {
		int u = read(), v = read();
		ll w = read();
		init(u, v, w);
		init(v, u, w);
	}
	d1(), d2();
	for(int i = 1; i <= cnt; ++i) {
		int from = edge[i].u, to = edge[i].v;
		ll val = edge[i].w;
		if(dis1[from] + val + dis2[to] == dis1[n])
			link(from, to);
	}
	dp(1);
	return !printf("%lld\n", ans);
}
