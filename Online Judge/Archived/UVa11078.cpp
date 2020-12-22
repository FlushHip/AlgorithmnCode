#include <stdio.h>

#define MAX(a,b) ((a)>(b)? (a):(b))

const int M=100000+5;

int n;
int a[M];

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		scanf("%d",&n);
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		int tmpmax=a[0];
		int ans=-150000*2-6;
		for(int i=1;i<n;i++)
			ans=MAX(ans,tmpmax-a[i]),
			tmpmax=MAX(tmpmax,a[i]);
		printf("%d\n",ans);
	}
	return 0;
}
