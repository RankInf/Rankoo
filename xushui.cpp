#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
#define double long double

const double eps = 1e-20;
int cas;
struct Line {
	double x1, y1, x2, y2;
}	A, B;
double cx, cy, ka, kb, ta, tb;
bool aa = 0, bb = 0;

double abss(double x) {return x + eps < 0 ? -x : x; }
bool find() {
	if(aa) {
		cx = A.x1, cy = kb * cx + tb;
		if(cy + eps < A.y1 || cy - eps > A.y2)
			return 0;
		return 1;
	}
	if(bb) {
		cx = B.x1, cy = ka * cx + ta;
		if(cy + eps < B.y1 || cy - eps > B.y2)
			return 0;
		return 1;
	}
	cx = -(ta - tb) / (ka - kb);
	cy = (ka * cx + ta);
	if(cy + eps < A.y1 || cy - eps > A.y2)
		return 0;
	if(cy + eps < B.y1 || cy - eps > B.y2)
		return 0;
	return 1;
}
double solve() {
	aa = bb = 0;
	if(abss(A.x1 - A.x2) <= eps)
		aa = 1;
	else {
		ka = (A.y1 - A.y2) / (A.x1 - A.x2);
		ta = A.y1 - ka * A.x1;
	}
	if(abss(B.x1 - B.x2) <= eps)
		bb = 1;
	else { 
		kb = (B.y1 - B.y2) / (B.x1 - B.x2);
		tb = B.y1 - kb * B.x1;
	}
	if((aa && bb) || abss(ka - kb) <= eps)
		return 0;
	if(abss(kb) <= eps || abss(ka) <= eps)
		return 0;
	if(!find())
		return 0;
	double tx = A.x2, ty = kb * tx + tb;
	double dy = A.y2, dx = (dy - tb) / kb;
	if(ty - eps >= A.y2 && ty + eps <= B.y2 && ty - eps >= dy)
		return 0;
	return 0.5 * abss((A.x2 - cx) * (dy - cy) - (dx - cx) * (A.y2 - cy));
}
int main() {
	freopen("xushui.in", "r", stdin);
	freopen("xushui.out", "w", stdout);
	scanf("%d", &cas);
	while(cas--) {
		double x1, y1, x2, y2, x3, y3, x4, y4;
		scanf("%Lf%Lf%Lf%Lf", &x1, &y1, &x2, &y2);
		if(y1 - eps > y2)
			swap(y1, y2), swap(x1, x2);
		A = (Line){x1, y1, x2, y2};
		scanf("%Lf%Lf%Lf%Lf", &x3, &y3, &x4, &y4);
		if(y3 - eps > y4)
			swap(y3, y4), swap(x3, x4);
		B = (Line){x3, y3, x4, y4};
		if(A.y2 - eps > B.y2)
			swap(A, B);
		printf("%.2Lf\n", solve());
	}
	return 0;
}
