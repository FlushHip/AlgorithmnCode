#include <stdio.h>
#include <string.h>

const int M=505;

int n,k;

int array[M];
int sum;

int ans[M];
int top;

bool judge(int x)
{
	int tmp=0;
	int i=n-1;
	while(tmp>=0){
		if(tmp+array[i]>x)
			ans[top++]=i;
		else
			tmp+=array[i];
		--i;
	}
	if(tmp>x)
		return false;
	if(top+1<=k)
		return true;
	return false;
}

void print()
{
	printf("%d",array[0]);
	int h=top-1;
	for(int i=0;i<n;i++){
		printf(" %d",array[i]);
		if(h<0)
			continue;
		if(i==ans[h])
			printf(" /"),
			--h;
	}
	puts("");
}

void work()
{
	int l=0,r=sum,mid;
	while(l<=r){
		mid=(l+r)/2;
		bool f=judge(mid);
		if(f)
			r=mid;
		else
			l=mid+1;
	}
}

int main()
{
	int N;
	for(scanf("%d",&N);N--;){
		scanf("%d%d",&n,&k);
		sum=0;
		for(int i=0;i<n;i++)
			scanf("%d",&array[i]),
			sum+=array[i];
		work();
		
		print();
	}
	return 0;
}
