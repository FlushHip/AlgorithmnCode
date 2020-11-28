import java.util.*;

public class POJ3267{
	
	static final int M=600+5;
	static final int E=300+5;
	
	Scanner cin=new Scanner(System.in);
	
	POJ3267(){
		while(cin.hasNext()){
			int W=cin.nextInt();
			int L=cin.nextInt();
			String msg=cin.next();
			String[] dirc=new String[M];
			for(int i=0;i<W;i++)
				dirc[i]=cin.next();
			int[] dp=new int[E];
			for(int i=0;i<E;i++)
				dp[i]=0;
			
			for(int i=0;i<L;i++){
				if(i==0)
					dp[0]=1;
				else
					dp[i]=dp[i-1]+1;
				for(int j=0;j<W;j++){
					int p_1=i;
					int p_2=dirc[j].length()-1;
					while(p_1>=0&&p_2>=0){
						if(dirc[j].charAt(p_2)==msg.charAt(p_1))
							--p_2;
						--p_1;
					}
					if(p_2<0)
						dp[i]=Math.min(dp[i],(p_1<0? 0:dp[p_1])+i-p_1-dirc[j].length());
				}
			}
			
			System.out.println(dp[L-1]);
		}
	}
	
	public static void main(String[] args){
		new POJ3267();
	}
}
