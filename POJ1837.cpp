#include <stdio.h>
#include <string.h>

const int offset=25*15*20;
const int G=20+1;
const int E=2*offset+5;

int dp[G][E];

int a[G],b[G];
int n,m;

int main()
{
	while(~scanf("%d%d",&n,&m)){
		int i,j,k;
		memset(dp,0,sizeof(dp));
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(i=1;i<=m;i++)
			scanf("%d",&b[i]);
		for(i=1;i<=n;i++)
			++dp[1][offset+b[1]*a[i]];

		for(i=2;i<=m;i++)
			for(j=-offset;j<=offset;j++)
				for(k=1;k<=n;k++)
					if(offset+j-b[i]*a[k]>0)
						dp[i][offset+j]+=dp[i-1][offset+j-b[i]*a[k]];
		printf("%d\n",dp[m][offset]);
	}
	return 0;
}
