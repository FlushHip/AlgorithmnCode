#include <stdio.h>
#include <string.h>

const int M=11;

int n;
int map[M][M];

int row[M];

int States[M][1<<M];
int top[M];

bool f;

int judge(int x)
{
	int sum=0;
	while(x){
		sum+=(x&1);
		x>>=1;
	}
	return sum;
}

void get_States()
{
	memset(top,0,sizeof(top));
	for(int i=0;i<(1<<n);i++){
		int tmp=judge(i);
		States[tmp][top[tmp]++]=i;
	}
}

void dfs(int x)
{
	if(x==n+1){
		f=true;
		return ;
	}
	if(f)
		return ;
	for(int i=0;i<top[row[x]];i++){
		int s=States[row[x]][i];
		if(s&(1<<(n-x)))
			continue;
		int tmp[M]={0};
		bool h=true;
		for(int j=n;j>=1&&s;j--,s>>=1)
			tmp[j]=(s&1);
		for(int j=1;j<x;j++)
			if(tmp[j]!=map[x][j]){
				h=false;
				break;
			}
		if(!h)
			continue;
		for(int j=x+1;j<=n;j++)
			map[x][j]=map[j][x]=tmp[j];
		dfs(x+1);
		if(f)
			return ;
		for(int j=x+1;j<=n;j++)
			map[j][x]=0;
	}
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
		get_States();
		memset(map,0,sizeof(map));		
		dfs(1);
		
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
