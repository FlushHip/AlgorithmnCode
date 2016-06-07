#include <stdio.h>
#include <string.h>

const int M=11;

int n;
int map[M][M];

int row[M];

bool f;

void dfs(int x,int y)
{
	if(y==n+1){
		int sum=0;
		for(int i=1;i<=n;i++)
			sum+=map[x][i];
		if(sum==row[x])
			dfs(x+1,x+2);
		return ;
	}
	if(x==n+1){
		f=true;
		return ;
	}
	if(f)
		return ;
	dfs(x,y+1);
	if(f)
		return ;
	map[x][y]=map[y][x]=1;
	dfs(x,y+1);
		
}

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		memset(row,0,sizeof(row));
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",&row[i]);
		f=false;
		memset(map,0,sizeof(map));		
		dfs(1,2);
		
		if(!f)
			puts("NO");
		else{
			puts("YES");
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					printf("%d%c",map[i][j],
						j==n? '\n':' ');
		}
		puts("");
	}
	return 0;
}
