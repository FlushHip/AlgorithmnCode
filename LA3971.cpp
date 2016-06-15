#include <stdio.h>
#include <string.h>

#include <string>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

const int M=1000+5;

typedef struct tagNode{
	int p;
	int q;
	tagNode(){}
	tagNode(int p,int q){
		this->p=p;
		this->q=q;
	}
}Node;

int n,b;

int top;

Node node[M][M];
int num[M];

map<string,int> has_map;

int count(string s)
{
	if(!has_map.count(s))
		has_map[s]=top++;
	return has_map[s];
}

bool judge(int x)
{
	int sum=0;
	for(int i=0;i<top;i++){
		bool f=false;
		int themin=b+10;
		for(int j=0;j<num[i];j++)
			if(x<=node[i][j].q&&themin>node[i][j].p){
				themin=node[i][j].p;
				f=true;
			}
		if(!f)
			return false;
		sum+=themin;
	}
	return sum<=b;
}

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		
		memset(num,0,sizeof(num));
		top=0;
		has_map.clear();
		
		scanf("%d%d",&n,&b);
		char tmp[35],t[35];
		int tp,tq;
		int ms=0;
		for(int i=0;i<n;i++){
			scanf("%s%s%d%d",tmp,t,&tp,&tq);
			ms=(ms<tq? tq:ms);
			int pos=count(tmp);
			node[pos][num[pos]++]=Node(tp,tq);
		}
		
		int l=1,r=ms,mid=0;
		while(l<r){
			mid=(r+l)/2;
			bool f=judge(mid);
			if(f)
				l=mid;
			else
				r=mid-1;
		}
		cout<<l<<endl;
	}
	return 0;
}
