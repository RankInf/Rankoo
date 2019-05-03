#include<cstdio>

const int MAXN = 111111;
int N;
char S[MAXN], T[MAXN];
int tr[MAXN][30], cnt = 0, fail[MAXN];
int q[MAXN], head = 1, tail = 0;

int low(char ch)
{
	return (ch >= 'A' && ch <= 'Z') ? 'a' + ch - 'A' : ch;
}
bool alpha(char ch)
{
	ch = low(ch);
	return ch >= 'a' && ch <= 'z';
}
void insert()
{
	int len = strlen(T + 1);
	int Now = 0;
	for(int i = 1; i <= len; ++i)
		if(tr[Now][low(T[i]) - 'a'])
			Now = tr[Now][low(T[i]) - 'a'];
		else
			Now = (tr[Now][low(T[i]) - 'a'] = ++cnt);
}
void build()
{
	for(int i = 0; i < 26; ++i)
		if(tr[0][i])
			q[++tail] = tr[0][i];
	while(head <= tail)
	{
		int p = q[head++];
		for(int i = 0; i < 26; ++i)
			if(tr[p][i])
				fail[tr[p][i]] = tr[fail[p]][i], q[++tail] = tr[p][i];
			else
				tr[p][i] = tr[fail[p]][i];
	}
}
void query()
{
	int len = strlen(S + 1);
}
int main()
{
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i)
	{
		scanf("%s", T + 1);
		insert(T);
	}
	build();
	scanf("%s", S + 1);
	query();
	puts(S + 1);
	return 0;
}
