import java.util.*;

public class UVa11520{
	Scanner cin=new Scanner(System.in);

	static final int M=10+5;
	
	static final int[] dirx=new int[]{0,0,1,-1};
	static final int[] diry=new int[]{1,-1,0,0};

	boolean f;

	void dfs(int x,int y,int n,char[][] map){
		if(x==n+1&&y==1){
			f=true;
			return ;
		}
		if(f)
			return ;
		int Y=(y+1>n? 1:y+1);
		int X=(Y==1? x+1:x);
		
		if(map[x][y]!='.'){
			dfs(X,Y,n,map);
			return ;
		}

		for(char c='A';c<='Z';c++){
			int m=0;
			for(int i=0;i<4;i++){
				int tx=x+dirx[i];
				int ty=y+diry[i];
				if(map[tx][ty]!=c)
					++m;
			}
			if(m==4){
				map[x][y]=c;
				dfs(X,Y,n,map);
				if(f)
					return ;
				map[x][y]='.';
			}
		}
	}

	UVa11520(){
		int K=1;
		int N=cin.nextInt();
		while(N-->0){
			int n=cin.nextInt();
			char[][] map=new char[M][M];
			for(int i=0;i<M;i++)
				for(int j=0;j<M;j++)
					map[i][j]='.';
			for(int i=1;i<=n;i++){
				char[] tmp=cin.next().toCharArray();
				for(int j=1;j<=n;j++)
					map[i][j]=tmp[j-1];
			}
			
			f=false;
			dfs(1,1,n,map);
			
			System.out.println("Case "+(K++)+":");
			for(int i=1;i<=n;i++){
				for(int j=1;j<=n;j++)
					System.out.print(map[i][j]);
				System.out.println();
			}
		}
	}

	public static void main(String[] args){
		new UVa11520();
	}
}
