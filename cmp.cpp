#include<cstdio>

double x1,x2,x,correct,ret=90000;
FILE *input,*output,*Std,*log;

double abs(double x){return x<0?-x:x;}

int main(int argc,char**argv)
{
	input=fopen("xushui.in","r");
	output=fopen("xushui.out","r");
	Std=fopen("xushui.ans","r");
	log=fopen("res.out","w");
	/*input=fopen(argv[1],"r");
	output=fopen(argv[2],"r");
	Std=fopen(argv[3],"r");
	log=fopen(argv[4],"w");*/
	for(int i=1;i<=100000;i++)
	{
		fscanf(output,"%lf",&x1);
		fscanf(Std,"%lf",&x2);
		if(abs(x1-x2)<=0.0001)++correct;
	}
	if(correct==100000)
	{
		fprintf(log,"1 Accepted\n");
		return 0;
	}
	if(correct<=ret)
	{
		fprintf(log,"0 Wa %.0lf %.0lf\n",correct,100000-correct);
		return 0;
	}
	x=(correct-ret)/(100000-ret)*(correct-ret)/(100000-ret)*(correct-ret)/(100000-ret);
	if(x<0.01)x=0.01;
	fprintf(log,"%.3lf Wa %.0lf %.0lf\n",x-0.01,correct,100000-correct);
	return 0;
}
