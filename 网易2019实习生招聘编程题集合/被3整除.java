import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static int fun(int x) {
		return x / 3 * 2 + (x % 3 == 0 ? 0 : x % 3 == 1 ? 0 : 1);
	}

	public static void main(String[] args) {
		while (cin.hasNext()) {
			int l = cin.nextInt(), r = cin.nextInt();
			System.out.println(fun(r) - fun(l - 1));
		}
	}
}
