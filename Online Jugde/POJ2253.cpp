#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX(a,b) ((a)>(b)? (a):(b))
#define MIN(a,b) ((a)<(b)? (a):(b))

const int M=200+5;

const int INF=0x3f3f3f3f;

typedef struct tagPoint{
	int x,y;
}Point;

int n;

Point points[M];

double map[M][M];

bool used[M];
double dis[M];

double dis2(Point a,Point b)
{
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

double dij(int src)
{
	int i,j;
	for(i=1;i<=n;i++)
		dis[i]=INF,used[i]=false;
	dis[src]=0;
	for(i=1;i<=n;i++){
		int pos=0;
		double tmp=INF;
		for(j=1;j<=n;j++)
			if(!used[j]&&tmp>dis[j])
				pos=j,tmp=dis[j];
		used[pos]=true;
		for(j=1;j<=n;j++)
			if(!used[j]){
				double ans=MAX(dis[pos],map[pos][j]);
				dis[j]=MIN(ans,dis[j]);
			}
	}
	return dis[2];
}

int main()
{
	int K=1;
	while(scanf("%d",&n),n){
		int i,j;
		int x,y;
		for(i=1;i<=n;i++){
			scanf("%d%d",&x,&y);
			points[i].x=x;
			points[i].y=y;
		}
		for(i=1;i<=n;i++)
			for(j=i;j<=n;j++)
				map[i][j]=map[j][i]=dis2(points[i],points[j]);

		double ans=sqrt(dij(1));
		printf("Scenario #%d\nFrog Distance = %.3f\n\n",K++,ans);
	}
	return 0;
}
