import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static void main(String[] args) {
		for (int T = cin.nextInt(); T-- > 0;) {
			int n = cin.nextInt(), ans = 0;
			String str = cin.next();
			for (int i = 0; i < str.length();) {
				for (; i < str.length() && str.charAt(i) == 'X'; ++i) {
				}
				for (; i < str.length() && str.charAt(i) == '.'; ++ans, i += 3) {
				}
			}
			System.out.println(ans);
		}
	}

}
