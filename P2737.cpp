#include<cstdio>
#include<algorithm>
#define min(_a, _b) (_a < (_b) ? _a : (_b))
#define max(_a, _b) (_a > (_b) ? _a : (_b))

const int base = 131, Hash = 19260817, Mod = 1e9 + 7; 
const int MAXN = 80010, MAXM = 100100;
int Pow[MAXM], Bitp[MAXM];
void Make()
{
	Pow[0] = 1;
	for(int i = 1; i <= MAXM; ++i)
		Pow[i] = (1ll * Pow[i - 1] % Hash * base % Hash) % Hash;
	Bitp[0] = 1;
	for(int i = 1; i <= MAXM; ++i)
		Bitp[i] = (1ll * Bitp[i - 1] % Mod * 2 % Mod);
}
int N, M, SS, TT;
struct Node
{
	int v, next, w;
}	edge[MAXM << 1];
int head[MAXN], cnt = 0;

int read()
{
	int a = 0;
	char ch;
	while((ch = getchar()) < 48);
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
void init(int x, int y, int z)
{
	edge[++cnt].v = y;
	edge[cnt].w = z;
	edge[cnt].next = head[x];
	head[x] = cnt;
}

int tot = 0, MAXW = 0;
int Ver[MAXN];
struct Tree
{
	int Ls, Rs;
	int Hash_sum;
	Tree()
	{
		Ls = Rs = Hash_sum = 0;
	}
}	T[8000100];

void pushup(int k, int l, int r)
{
	int mid = (l + r) >> 1;
	T[k].Hash_sum = (1ll * T[T[k].Ls].Hash_sum * Pow[r - mid] % Hash + T[T[k].Rs].Hash_sum % Hash) % Hash;
}
bool Cmp(int k1, int k2, int l, int r)
{
	if(l == r)
		return T[k1].Hash_sum < T[k2].Hash_sum;
	int mid = (l + r) >> 1;
	if(T[T[k1].Rs].Hash_sum == T[T[k2].Rs].Hash_sum)	
		return Cmp(T[k1].Ls, T[k2].Ls, l, mid);
	else
		return Cmp(T[k1].Rs, T[k2].Rs, mid + 1, r);
}
int Find(int k, int l, int r, int pos)
{
	if(T[k].Hash_sum == 0)
		return max(pos, l);
	if(l == r)
		return -1;
	int mid = (l + r) >> 1;
	int Res;
	if(pos <= mid && ~(Res = Find(T[k].Ls, l, mid, pos)))
		return Res;
	else
		return Find(T[k].Rs, mid + 1, r, pos);
}
void Modify(int &k, int l, int r, int x, int y)
{
	if(x > y)
		return ;
	T[++tot] = T[k];
	k = tot;
	if(x <= l && r <= y)
	{
		T[k].Hash_sum = 0;
		T[k].Ls = T[k].Rs = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
		Modify(T[k].Ls, l, mid, x, y);
	if(y > mid)
		Modify(T[k].Rs, mid + 1, r, x, y);
	pushup(k, l, r);
}
void Set(int &k, int l, int r, int pos)
{
	T[++tot] = T[k];
	k = tot;
	if(l == r)
	{
		T[k].Hash_sum = base * 1 % Hash;
		return ;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid)
		Set(T[k].Ls, l, mid, pos);
	else
		Set(T[k].Rs, mid + 1, r, pos);
	pushup(k, l, r);
}

struct Data
{
	int idx;
	int root;
	bool operator <(const Data &val)const
	{
		return Cmp(val.root, root, 0, MAXW + 20);
	}
};
struct Ltree
{
	Data key[MAXN + MAXM << 1];
	int siz;
	void push(const Data &val)
	{
		key[++siz] = val;
		std::push_heap(key + 1, key + siz + 1);
	} 		
	Data top()
	{
		return key[1];
	}
	void pop()
	{
		std::pop_heap(key + 1, key + siz + 1);
		--siz;
	}
	bool empty()
	{
		return siz == 0;
	}
}	Ltr;

bool vis[MAXN];
void Dijkstra()
{
	Ltr.push((Data){SS, 0});
	Ver[SS] = 0;
	while(!Ltr.empty())
	{
		Data temp = Ltr.top();
		Ltr.pop();
		int from = temp.idx;
		if(vis[from])
			continue;
		Ver[from] = temp.root;
		vis[from] = 1;
		for(int k = head[from]; k; k = edge[k].next)
		{
			int to = edge[k].v;
			int cur = Find(Ver[from], 0, MAXW + 20, edge[k].w);
			int tp = temp.root;
			Modify(tp, 0, MAXW + 20, edge[k].w, cur - 1);
			Set(tp, 0, MAXW + 20, cur);
			Ltr.push((Data){to, tp});
		}
	}
}
int Calc(int k, int l, int r)
{
	if(T[k].Hash_sum == 0)
		return 0;
	if(l == r)
		return Bitp[l] % Mod;
	int mid = (l + r) >> 1;
	return (Calc(T[k].Ls, l, mid) % Mod + Calc(T[k].Rs, mid + 1, r) % Mod) % Mod;
}
int main()
{
	freopen("input.in", "r", stdin);
	Make();
	N = read(), M = read();
	for(int i = 1; i <= M; ++i)
	{
		int x = read(), y = read(), z = read();
		init(x, y, z);
		init(y, x, z);
		MAXW = max(MAXW, z);
	}
	SS = read(), TT = read();
	Dijkstra();
	printf("%d\n", Calc(Ver[TT], 0, MAXW + 20));
	return 0;
}
