//T2
#include<cstdio>
#include<cstring>
#include<algorithm>
#define R register
#define MAXN 6010
using namespace std;
int F[MAXN][MAXN],n,A[MAXN],G[MAXN][MAXN],H[MAXN][MAXN];
int main(){
	scanf("%d",&n);
	for(R int i = 1; i <= n; i++) scanf("%d",A+i);
	for(R int i = 1; i <= n; i++){
		int MX = A[i], MN = A[i];
		for(R int j = i; j; j--){
			MX = max(MX,A[j]); MN = min(MN,A[j]);
			G[i][i - j + 1] = MX - MN;
		} G[i][i + 1] = 0x3f3f3f3f;
	}
	F[1][1] = H[1][1] = 1;
	for(R int i = 2; i <= n; i++){
		int MX = A[i], MN = A[i];
		for(R int j = i; j; j--){
			MX = max(MX,A[j]); MN = min(MN,A[j]);
			int k = lower_bound(G[j-1] + 1, G[j-1] + j + 1, MX - MN) - G[j-1] - 1; 
			k = j - k;
		//	printf("k = %d\n",k);
			F[i][j] = H[j-1][k] + 1;
		//	printf("F[%d][%d] = %d\n",i,j,F[i][j]);
		} H[i][i] = F[i][i];
		for(R int j = i - 1; j; j--)
			H[i][j] = max(F[i][j],H[i][j+1]);//, printf("H[%d][%d] = %d\n",i,j,H[i][j]);
	} printf("%d",H[n][1]);
	return 0;
}
