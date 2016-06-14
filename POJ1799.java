import java.util.*;

public class POJ1799{

	Scanner cin=new Scanner(System.in);

	POJ1799(){
		int K=1;
		int N=cin.nextInt();
		while(N-->0){
			double R=cin.nextDouble();
			int n=cin.nextInt();
			double tmp=Math.sin(Math.PI/n);
			double r=R*tmp/(1+tmp);
			System.out.println(String.format("Scenario #%d:\n%.3f\n",K++,r));
		}
	}

	public static void main(String[] args){
		new POJ1799();
	}
}
