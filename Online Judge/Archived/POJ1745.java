import java.util.*;

public class Main
{
	Scanner cin=new Scanner(System.in);
	
	static final int M=10000+5;
	static final int E=100+5;
	
	int n,k;
	int[] a=new int[M];
	
	boolean[][] dp=new boolean[M][E];
	
	Main(){
		while(cin.hasNext()){
			n=cin.nextInt();
			k=cin.nextInt();
			for(int i=0;i<n;i++){
				a[i]=cin.nextInt();
				a[i]=(a[i]<0? -a[i]:a[i]);
				a[i]%=k;
			}
			
			for(int i=0;i<M;i++)
				for(int j=0;j<E;j++)
					dp[i][j]=false;
			dp[0][a[0]]=true;
			
			for(int i=1;i<M;i++)
				for(int j=0;j<k;j++)
					dp[i][j]=(dp[i-1][(j-a[i]+k)%k]||dp[i-1][(j+a[i])%k]);
			System.out.println(dp[n-1][0]? "Divisible":"Not divisible");
		}
	}
	
	public static void main(String[] args){
		new Main();
	}
}
