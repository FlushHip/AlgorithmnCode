import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static void main(String[] args) {
		String DIR = "NESW";
		while (cin.hasNext()) {
			int n = cin.nextInt();
			String str = cin.next();
			int ans = 0;
			for (int i = 0; i < n; i++)
				ans = (ans + (str.charAt(i) == 'L' ? -1 : 1) + 4) % 4;
			System.out.println(DIR.charAt(ans % 4));
		}
	}
}
