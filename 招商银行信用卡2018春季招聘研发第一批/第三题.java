import java.util.*;

public class Main {

	public Scanner cin = new Scanner(System.in);

	Main() {
		while (cin.hasNext()) {
			long n = cin.nextLong(), ans = n / 2 * (n - n / 2);
			for (int i = 1; i <= n / 2; i++) {
				if (n / i <= n % i)
					continue;
				ans = (long) Math.max(ans, Math.pow(i + 1, n % i) * Math.pow(i, n / i - (n % i)));
			}
			System.out.println(ans);
		}
	}

	public static void main(String[] args) {
		new Main();
	}
}
