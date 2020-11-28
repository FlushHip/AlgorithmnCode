#include <stdio.h>

const int M=105;

int main()
{
	int n;
	while(scanf("%d",&n),n){
		int x;
		int cnt[M]={0};
		for(int i=0;i<n;i++)
			scanf("%d",&x),
			++cnt[x];
		bool f=false;
		for(int i=0;i<M;i++)
			for(int j=0;j<cnt[i];j++)
				if(!f)
					printf("%d",i),
					f=true;
				else
					printf(" %d",i);
		puts("");
	}
	return 0;
}
