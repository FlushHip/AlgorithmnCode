#include <iostream>
#include <string>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

typedef struct tagPoint{
	int x,y;
	int s;
	tagPoint(){}
	tagPoint(int X,int Y,int S):
		x(X),y(Y),s(S){}
}Point;

const int M=50+5;

const int E=200+5;

const int dirx[]={0,0,1,-1};
const int diry[]={1,-1,0,0};

int n,m;

char map[M][M];
int pos[M][M];
int top=0;

bool used[M][M];

int dp[E][E];

int dis[E];
bool vis[E];

void bfs_init(Point src,int index)
{
	dp[index][index]=0;
	queue<Point> que;
	memset(used,false,sizeof(used));
	que.push(src);
	used[src.x][src.y]=true;
	while(!que.empty()){
		Point pre=que.front();
		que.pop();
		int i;
		for(i=0;i<4;i++){
			int tx=pre.x+dirx[i];
			int ty=pre.y+diry[i];
			if(tx>=1&&tx<=n&&ty>=1&&ty<=m&&
				map[tx][ty]!='#'&&!used[tx][ty]){
				if(pos[tx][ty])
					dp[index][pos[tx][ty]]=pre.s+1;
				Point now=Point(tx,ty,pre.s+1);
				used[tx][ty]=true;
				que.push(now);
			}
		}
	}
}

void init()
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(pos[i][j])
				bfs_init(Point(i,j,0),pos[i][j]);
}

int prim(int src)
{
	int ans=0;
	int i,j;
	for(i=1;i<=top;i++)
		dis[i]=0x3f3f3f3f,
		vis[i]=false;
	dis[src]=0;
	for(i=1;i<=top;i++){
		int tmp=0x3f3f3f3f,pos=0;
		for(j=1;j<=top;j++)
			if(!vis[j]&&tmp>dis[j])
				tmp=dis[j],pos=j;
		if(!pos)
			break;
		vis[pos]=true;
		ans+=tmp;
		for(j=1;j<=top;j++)
			if(!vis[j]&&dis[j]>dp[pos][j])
				dis[j]=dp[pos][j];
	}
	return ans;
}

int main()
{
	int N;
	for(cin>>N;N--;){
		top=0;
		memset(pos,0,sizeof(pos));
		cin>>m>>n;
		int c;
		while((c=getchar())==' ');
		int i,j;
		for(i=1;i<=n;i++){
			char str[M];
			gets(str);
			string tmp=str;
			for(j=1;j<=m;j++){
				if(j>tmp.size())
					map[i][j]='#';
				else
					map[i][j]=tmp.at(j-1);
				if(map[i][j]=='S'||map[i][j]=='A')
					pos[i][j]=++top;
			}
		}
		init();
		int ans=prim(1);
		cout<<ans<<endl;
	}
	return 0;
}
