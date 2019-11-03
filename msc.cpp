#include<cstdio>

const int maxn = 2e5 + 10;
typedef long long ll;
int n, res, S[2][maxn], siz[2], trie[2][maxn * 60], tot;
ll ar[maxn], maxa, maxb;

ll read() {
	ll a = 0;
	char ch;
	while((ch = getchar()) < 48);
	while(ch >= 48 && ch <= 57) a = (a << 3) + (a << 1) + (ch ^ 48), ch = getchar();
	return a;
}
void build(ll x) {
	int now = 0, cnt = res;
	for(; ~cnt; cnt--)
		now = trie[x & (1ll << cnt) > 0][now] ? trie[x & (1ll << cnt) > 0][now] : (trie[x & (1ll << cnt) > 0][now] = ++tot);
}
ll query(ll x) {
	int now = trie[0][0], cnt = res - 1;
	ll cur = 1ll << res;
	for(; now && (~cnt); cnt--) {
		int tmp = trie[x & (1ll << cnt) > 0][now];
		if(!tmp)
			tmp = trie[(x & (1ll << cnt) > 0) ^ 1][now], cur |= (1ll << cnt);
		now = tmp;
	}
	return cur;			
}
int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		ar[i] = read(), ar[i] > maxa ? maxa = ar[i] : 0;
	while((1 << maxb) <= n)
		maxb++;
	res = maxb - 1;
	for(bool flag = 1; flag && (~res); res--) {
		ll x = 1ll << res, last = ar[1] & x;
		for(int i = 2; i <= n; ++i)
			if((ar[i] & x) != last) {
				flag = 0;
				break;
			}
		if(!flag)
			break;
	}
	if(res < 0)
		return puts("0"), 0;
	for(int i = 1; i <= n; ++i)
		(1ll << res) & ar[i] ? S[1][++siz[1]] = ar[i] : S[0][++siz[0]] = ar[i];
	for(int i = 1; i <= siz[0]; ++i)
		build(S[0][i]);
	ll ans = 1ll << 62;
	for(int i = 1; i <= siz[1]; ++i) {
		ll tmp = query(S[1][i]);
		tmp < ans ? ans = tmp : 0;
	}
	printf("%lld\n", ans);
	return 0;
}
