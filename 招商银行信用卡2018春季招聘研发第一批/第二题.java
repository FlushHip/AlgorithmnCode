import java.util.*;

public class Main {

	public Scanner cin = new Scanner(System.in);
	
	public int n;
	public ArrayList<String> ans = new ArrayList<String>();
	
	public void dfs(int x, int l, int r, String str) {
		if (x == 2 * n) {
			ans.add(str);
			return ;
		}
		if (l < n)
			dfs(x + 1, l + 1, r, str + "(");
		if (r < n && l > r)
			dfs(x + 1, l, r + 1, str + ")");
	}

	Main() {
		while (cin.hasNext()) {
			n = cin.nextInt();
			ans.clear();
			dfs(0, 0, 0, "");
			for (int i = 0; i < ans.size(); i++)
				System.out.print(ans.get(i) + (i != ans.size() - 1 ? "," : "\n"));
		}
	}

	public static void main(String[] args) {
		new Main();
	}
}
