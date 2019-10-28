//T3
#include<cstdio>
#include<cstring>
#include<bitset>
#include<algorithm>
#define R register
#define MAXN 30010
#define MAXM 600010
#define LL long long
using namespace std;
int head[MAXN],point[MAXM<<1],next[MAXM<<1],W[MAXM<<1],used = 1,d[MAXN];
int n,m; LL Dis[MAXN],Ans; bool vis[MAXN];
bitset<MAXN> F[MAXN];
inline void add(int u,int v,int w){
	point[++used] = v;
	next[used] = head[u];
	head[u] = used; W[used] = w;
}
bool CMP(int u,int v) {return Dis[u] > Dis[v];}
struct Heap{
	int h[MAXM],size;
	void push(int u){
		h[++size] = u;
		push_heap(h+1,h+size+1,CMP);
	}
	int pop(){
		int res = h[1];
		pop_heap(h+1,h+size--+1,CMP);
		return res;
	}
	bool empty(){
		return !size;
	}
}H;
struct Queue{
	int q[MAXN],h,t;
	void push(int u){
		q[++t] = u;
	}
	int pop(){
		return q[++h];
	}
	bool empty(){
		return h == t;
	}
}Q;
void Dijkstra(){
	for(R int i = 2; i <= n; i++) Dis[i] = 1ll << 60;
	H.push(1);
	while(!H.empty()){
		int u = H.pop(); if(vis[u]) continue; vis[u] = 1;
		for(int k = head[u]; k; k = next[k]){
			int v = point[k];
			if(Dis[v] > Dis[u] + W[k]){
				Dis[v] = Dis[u] + W[k];
				H.push(v);
			}
		}
	}
}
void DFS(int u){
	for(int k = head[u]; k; k = next[k]){
		int v = point[k];
		if(Dis[v] + W[k] == Dis[u]){
			++d[v];
			DFS(v);
		}
	}
}
void Topsort(){
	Q.push(n);
	while(!Q.empty()){
		int u = Q.pop();
		for(int k = head[u]; k; k = next[k]){
			int v = point[k];
			if(Dis[v] + W[k] == Dis[u]){
					F[v] |= F[u]; F[v][u] = 1;
					Q.push(v);
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(R int i = 1; i <= m; i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		add(u,v,w); add(v,u,w);
	}
	Dijkstra(); DFS(n); Topsort();
/*	for(R int i = 1; i <= n; i++){ printf("%d:",i);
		for(R int j = 1; j <= n; j++) printf("%d",F[i][j] & 1); puts("");
	}*/
	for(R int i = 1; i <= n; i++) Ans += F[i].count();
	printf("%lld",Ans);
}
