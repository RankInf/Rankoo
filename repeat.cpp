#include<cstdio>
#include<cstring>
#define Min(_a, _b) (_a < _b ? _a : _b)
typedef unsigned long long ull;

const ull base = 19260817;
const int maxn = 1e6 + 10;
int n, m, len, ans;
ull hash[maxn], pow[maxn], temp[maxn];
bool vis[maxn];
char s[maxn];

ull gethash(int l, int r) {return hash[r] - hash[l - 1] * pow[r - l + 1]; }
int main() {
	scanf("%d%s", &n, s + 1);
	pow[0] = 1;
	for(int i = 1; i <= n; ++i)
		hash[i] = hash[i - 1] * base + (s[i] - 'a'), pow[i] = pow[i - 1] * base;
	for(int k = 1; k <= n; ++k) {
		ull last = gethash(1, k);
		vis[k] = 1;
		for(int i = k + 1; i <= n; i += k) {
			int j = Min(n, i + k - 1);
			if(j - i + 1 < k) {
				if(gethash(1, j - i + 1) != gethash(i, j)) {
					vis[k] = 0;
					break;
				}
			}
			else
				if(gethash(i, j) != last) {
					vis[k] = 0;
					break;
				}
		}		
	}
	scanf("%d", &m);
	while(m--) {
		scanf("%s", s + 1);
		len = strlen(s + 1);
		if(!vis[len])
			continue;
		ull temp = 0;
		for(int i = 1; i <= len; ++i)
			temp = temp * base + (s[i] - 'a');
		if(temp == gethash(1, len))
			ans++;
	}
	printf("%d\n", ans);
	return 0;
}
