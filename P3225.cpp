#include<cstdio>
#include<cstring>
#define max(_a, _b) (_a > (_b) ? _a : (_b))
#define min(_a, _b) (_a < (_b) ? _a : (_b))
typedef unsigned long long ull;

const ull base = 13331;
int N, M;
int k;
char S[11111], T[1111];
ull Pow[11111], Hs[11111], Temp[25];
int D[25];

int l, r;
ull GetS(int s, int t)
{
	return Hs[t] - Hs[s - 1] * Pow[t - s + 1];
}
bool check(int u, int v, int p, int q)
{
	if(u > v)
		return 0;
	int tot = 1;
	for(int i = 1; i < 25; ++i)
		D[i] = 0, Temp[i] = 0;
	for(int i = u; i <= v; ++i)
	{
		if(T[i] == '?')
			++tot;
		else
			D[tot]++, Temp[tot] = Temp[tot] * base + T[i];
	}
	for(int i = p; i <= N - q + 1; ++i)
	{
		bool book = 1;
		int now = i;
		for(int j = 1; j <= tot; ++j)
		{
			if(GetS(now, now + D[j] - 1) != Temp[j])
			{
				book = 0;
				break;
			}
			now += D[j] + 1;
		}
		if(book)
		{
			l = min(l, i);
			r = max(r, i + q - 1);
			return 0;
		}
	}
	return 1;
}
int main()
{
	scanf("%s%d", S + 1, &k);
	N = strlen(S + 1);
	Pow[0] = 1;
	for(int i = 1; i <= N; ++i)
		Pow[i] = Pow[i - 1] * base;
	for(int i = 1; i <= N; ++i)
		Hs[i] = Hs[i - 1] * base + S[i];
	while(k--)
	{
		scanf("%s", T + 1);
		M = strlen(T + 1);
		l = N + 1, r = 0;
		if(T[1] == '*')
			l = 1;
		int Last = 1;
		bool flag = 1;
		for(int i = 1; i <= M; ++i)
		{
			if(T[i] == '*')
			{
				if(check(Last, i - 1, r + 1, i - Last))
				{
					flag = 0;
					break;
				}
				Last = i + 1;
			}
		}
		if(check(Last, M, r + 1, M - Last + 1))
			flag = 0;
		(flag) ? printf("%d %d\n", l , r) : puts("0 0");
	}
	return 0;
}
