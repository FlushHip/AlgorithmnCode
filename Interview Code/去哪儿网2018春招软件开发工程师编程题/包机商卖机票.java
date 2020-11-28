import java.util.*;

public class Main {

	public Scanner cin = new Scanner(System.in);

	Main() {
		while (cin.hasNext()) {
			int n = cin.nextInt(), m = cin.nextInt();
			boolean isOk = false;
			ArrayList<Integer> arr = new ArrayList<Integer>();
			for (int i = 0, x; i < n; i++)
				if ((x = cin.nextInt()) <= m)
					arr.add(x);
			for (int i = 0; i < (1 << arr.size()); i++) {
				int sum = 0;
				for (int bit = 0; bit < arr.size(); bit++)
					if ((i & (1 << bit)) != 0)
						sum += arr.get(bit);
				if (sum == m) {
					isOk = true;
					break;
				}
			}
			System.out.println(isOk ? "perfect" : "good");
		}
	}

	public static void main(String[] args) {
		new Main();
	}
}
