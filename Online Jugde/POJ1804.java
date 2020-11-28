import java.util.*;

public class POJ1804{
	Scanner cin=new Scanner(System.in);

	static final int M=1000+5;

	POJ1804(){
		int K=1;
		int N=cin.nextInt();
		while(N-->0){
			int n=cin.nextInt();
			int[] a=new int[M];
			for(int i=0;i<n;i++)
				a[i]=cin.nextInt();
			int sum=0;
			for(int i=0;i<n-1;i++)
				for(int j=i+1;j<n;j++)
					sum+=(a[i]>a[j]? 1:0);
			System.out.println(String.format("Scenario #%d:\n%d\n",K++,sum));
		}
	}

	public static void main(String[] args){
		new POJ1804();
	}
}
