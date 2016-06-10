#include <iostream>
#include <algortithm>

using namespace std;

const int M=10000+5;

int n;

int de[M];

bool havel()
{
	for(int i=0;i<n;i++){
		sort(de+i,de+n);
		if(de[i]<0)
			return false;
		for(int j=i+1;j<n&&de[i];j++)
			--de[j],--de[i];
	}
	return true;
}

int main()
{
	while(cin>>n,n){
		for(int i=0;i<n;i++)
			cin>>de[i];
		bool f=havel();
		cout<<(f? "Possible":"Not possible")<<endl;
	}
	return 0;
}
