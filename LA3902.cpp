#include <stdio.h>
#include <string.h>

#include <iostream>
#include <vector>

using namespace std;

const int M=1000+5;

int n;
int VOD,k;

vector<int> edge[M];
vector<int> leaf[M];

bool cover[M];
int p[M];

void dfs_init(int to,int from,int h)
{
	p[to]=from;
	if(edge[to].size()==1&&h>k)
		leaf[h].push_back(to);
	for(int i=0;i<edge[to].size();i++)
		if(edge[to].at(i)!=from)
			dfs_init(edge[to].at(i),to,h+1);
}

void dfs_cov(int to,int from,int h)
{
	if(h==k)
		return ;
	for(int i=0;i<edge[to].size();i++)
		if(edge[to].at(i)!=from)
			cover[edge[to].at(i)]=true,
			dfs_cov(edge[to].at(i),to,h+1);
}

int work()
{
	int sum=0;
	for(int h=n-1;h>k;h--){
		for(int i=0;i<leaf[h].size();i++){
			int point=leaf[h].at(i);
			if(cover[point])
				continue;
			else{
				++sum;
				int start=point;
				for(int L=0;L<k;L++)
					start=p[start];
				dfs_cov(start,-1,0);
			}
		}
	}
	return sum;
}

int main()
{
	int N;
	for(cin>>N;N--;){
		for(int i=0;i<M;i++)
			edge[i].clear(),leaf[i].clear();
		memset(cover,false,sizeof(cover));
		cin>>n>>VOD>>k;
		int x,y;
		for(int i=0;i<n-1;i++)
			scanf("%d%d",&x,&y),
			edge[x].push_back(y),
			edge[y].push_back(x);
		dfs_init(VOD,-1,0);

		int ans=work();
		cout<<ans<<endl;
	}
	return 0;
}
