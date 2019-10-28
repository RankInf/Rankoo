//T1
#include<cstdio>
#include<cstring>
#define R register
#define MAXN 1000010
using namespace std;
int n,m,fa[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	if(n == 0) return !puts("-1");
	if(n == 1 && m != 1) return !puts("-1");
	if(n == 1) return 0;
	int cnt = 1,now = n;
	for(R int i = 1; i <= n; i++) fa[i] = i - 1;
	while(cnt < m){
		if(now - 2 <= 0) break;
		fa[now] = now - 2; ++cnt; now = now - 2;
	}
	if(cnt != m) return !puts("-1");
	for(R int i = 2; i <= n; i++)
		printf("%d\n",fa[i]);
	return 0;
}
