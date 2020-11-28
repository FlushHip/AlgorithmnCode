#include <stdio.h>
#include <string.h>

#include <string>
#include <algorithm>
#include <iostream>

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
string tag[M];

Node node[M][M];
int num[M];

bool cmp(Node a,Node b)
{
	return a.p<b.p;
}

int count(string s)
{
	for(int i=0;i<top;i++)
		if(s==tag[i])
			return i;
	tag[top]=s;
	return top++;
}

bool judge(int x)
{
	int sum=0;
	for(int i=0;i<top;i++){
		bool f=false;
		for(int j=0;j<num[i];j++)
			if(x<=node[i][j].q){
				sum+=node[i][j].p;
				f=true;
				break;
			}
		if(!f)
			return false;
	}
	return sum<=b;
}

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		
		memset(num,0,sizeof(num));
		top=0;
		
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
		for(int i=0;i<top;i++)
			sort(node[i],node[i]+num[i],cmp);
		
		int l=1,r=ms,mid=0;
		while(l<r){
			mid=(r+l+1)/2;
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
