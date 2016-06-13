import java.util.*;

public class POJ1837{
	
	static final int M=20+5;
	static final int E=(int)1e6;

	int[] que=new int[E];
	int[] pos=new int[E];
	int head,tail;

	int[] a=new int[M],b=new int[M];

	int n,m;

	Scanner cin=new Scanner(System.in);

	void start(){
		while(cin.hasNext()){
			n=cin.nextInt();
			m=cin.nextInt();
			for(int i=1;i<=n;i++)
				a[i]=cin.nextInt();
			for(int i=1;i<=m;i++)
				b[i]=cin.nextInt();
			
			int ans=0;

			head=0;
			tail=0;
			pos[tail]=0;
			que[tail]=0;
			++tail;
			while(head!=tail){
				int t_pos=pos[head];
				int pre=que[head++];
				head%=E;

				for(int i=1;i<=n;i++){
					int tmp=b[t_pos+1]*a[i];
					if(t_pos+1==m){
						ans+=((pre+tmp)==0? 1:0);
						continue;
					}
					que[tail]=pre+tmp;
					pos[tail++]=t_pos+1;
					tail%=E;
				}
			}
			System.out.println(ans);
		}
	}
	public static void main(String[] args){
		new POJ1837().start();
	}
}
