import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static void main(String[] args) {
		while (cin.hasNext()) {
			long n = cin.nextLong(), k = cin.nextLong(), ans = 0;
			if (k == 0)
				ans = n * n;
			else
				for (long y = k + 1; y <= n; y++)
					ans += n / y * (y - k) + (n % y >= k ? n % y - k + 1 : 0);
			System.out.println(ans);
		}
	}

}
