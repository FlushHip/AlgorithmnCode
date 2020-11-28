#include <stdio.h>
#include <string.h>

const int M=64;

typedef long long LL;

int n;

int src[M],des[M];

LL dfs(int a[],int x,int num)
{
	if(!x)
		return 0;
	if(a[x]==num)
		return dfs(a,x-1,num);
	return dfs(a,x-1,6-num-a[x])+(1LL<<(x-1));
}

int main()
{
	int K=1;
	while(scanf("%d",&n),n){
		for(int i=1;i<=n;i++)
			scanf("%d",&des[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&src[i]);
		int top=n;
		for(;top>=1&&des[top]==src[top];--top);
		printf("Case %d: ",K++);
		if(!top)
			puts("0");
		else
			printf("%lld\n",
				dfs(src,top-1,6-src[top]-des[top])+
				dfs(des,top-1,6-src[top]-des[top])+
				1LL);
	}
	return 0;
}
