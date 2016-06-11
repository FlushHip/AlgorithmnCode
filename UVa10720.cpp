#include <iostream>
#include <algorithm>

using namespace std;

const int M=10000+5;

int n;

int de[M];

bool cmp(int a,int b)
{
	return a>b;
}

bool havel()
{
	for(int i=0;i<n;i++){
		sort(de+i,de+n,cmp);
		if(de[i]<0)
			return false;
		if(!de[i])
			break;
		for(int j=i+1;j<n&&de[i];j++){
			--de[j],--de[i];
			if(de[j]<0)
				return false;
		}
		if(de[i]>0)
			return false;
	}
	return true;
}

int main()
{
	std::ios::sync_with_stdio(false);
	while(cin>>n,n){
		for(int i=0;i<n;i++)
			cin>>de[i];
		bool f=havel();
		cout<<(f? "Possible":"Not possible")<<endl;
	}
	return 0;
}
