#include<cstdio>
#include<algorithm>
#define lowbit(x) (x & (-x))

const int MAXN = 111111, Mod = 99999997;
int N;
struct Data
{
	int idx, val;
	bool operator <(const Data &DD)const
	{
		return (val < DD.val) ? 1 : (val == DD.val && idx < DD.idx);
	}
}	A[MAXN], B[MAXN];
int rk[MAXN], C[MAXN], Ans = 0;

int read()
{
	int a = 0;
	char ch;
	while((ch = getchar()) < 48) ;
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
int main()
{
	N = read();
	for(int i = 1; i <= N; ++i)
		A[i].val = read(), A[i].idx = i;
	for(int i = 1; i <= N; ++i)
		B[i].val = read(), B[i].idx = i;
	std::sort(A + 1, A + N + 1);
	std::sort(B + 1, B + N + 1);
	for(int i = 1; i <= N; ++i)
		rk[A[i].idx] = B[i].idx;
	for(int i = N; i >= 1; --i)
	{
		for(int j = rk[i] - 1; j > 0; j -= lowbit(j))
		{
			Ans += C[j];
			Ans >= Mod ? Ans -= Mod : 0;
		}
		for(int j = rk[i]; j <= N; j += lowbit(j))
		{
			C[j]++;
			C[j] >= Mod ? C[j] -= Mod : 0;
		}
	}
	return !printf("%d\n", Ans % Mod);
}
