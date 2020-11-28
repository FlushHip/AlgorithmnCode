import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static int lower_bound(int[] arr, int begin, int end, long tag) {
		while (begin < end) {
			int mid = (begin + end) / 2;
			if (arr[mid] < tag)
				begin = mid + 1;
			else
				end = mid;
		}
		return begin;
	}

	public static void main(String[] args) {
		while (cin.hasNext()) {
			int n = cin.nextInt();
			int[] arr = new int[n];
			for (int i = 0; i < n; arr[i++] = cin.nextInt() * 60
					+ cin.nextInt()) {
			}
			Arrays.sort(arr);
			int x = cin.nextInt();
			int index = lower_bound(arr, 0, n,
					cin.nextInt() * 60 + cin.nextInt() - x + 1) - 1;
			System.out.println(arr[index] / 60 + " " + arr[index] % 60);
		}
	}
}
