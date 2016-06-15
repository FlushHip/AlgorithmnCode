#include <stdio.h>
#include <string.h>

const int M=500+5;

int n,m;

int a[M],b[M];

int dp[M][M];

int main()
{
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		scanf("%d",&m);
		for(int i=0;i<m;i++)
			scanf("%d",&b[i]);
		memset(dp,0,sizeof(dp));
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(a[i]!=b[j])
					dp[i][j]=dp[i-1][j];
				else{
					for(int k=j-1;k>=1;k--)
						if(dp[i-1][j])
				}
			}
	}
	return 0;
}
