#include <stdio.h>
#include <string.h>

const int M=505;

int n,k;

int array[M];
int sum;

bool ans[M];
int top;

bool judge(int x)
{
	top=0;
	memset(ans,false,sizeof(ans));
	int tmp=0;
	int i=n-1;
	while(i>=0){
		if(array[i]>x)
			return false;
		if(tmp+array[i]>x)
			ans[i]=true,
			++top,
			tmp=0,
			++i;
		else
			tmp+=array[i];
		--i;
	}
	return top+1<=k;
}

void print()
{
	printf("%d",array[0]);
	if(ans[0])
		printf(" /");
	for(int i=1;i<n;i++){
		printf(" %d",array[i]);
		if(ans[i])
			printf(" /");
	}
	puts("");
}

void work()
{
	int l=0,r=sum,mid;
	while(l<r){
		mid=(l+r)/2;
		bool f=judge(mid);
		if(f)
			r=mid;
		else
			l=mid+1;
	}
	judge(l);
	
	for(int i=0;i<n&&top+1<k;i++)
		if(!ans[i])
			ans[i]=true,
			top++;
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

