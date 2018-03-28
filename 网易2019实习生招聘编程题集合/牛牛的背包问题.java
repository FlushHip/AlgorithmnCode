import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static int lower_bound(long[] arr, int begin, int end, long tag) {
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
			long n = cin.nextLong(), w = cin.nextLong();
			long[] v = new long[(int) n];
			for (int i = 0; i < n; v[i++] = cin.nextLong()) {
			}
			long n1 = n >> 1, n2 = n - n1;
			long[] arr = new long[1 << n1];
			for (int i = 0; i < (1 << n1); i++) {
				long sum = 0;
				for (int bits = 0; bits < n1; bits++)
					sum += (long) (((i & (1 << bits)) != 0) ? v[bits] : 0);
				arr[i] = sum;
			}
			Arrays.sort(arr);

			long ans = 0;
			for (int i = 0; i < (1 << n2); i++) {
				long sum = 0;
				for (int bits = 0; bits < n2; bits++)
					sum += (long) (((i & (1 << bits)) != 0) ? v[(int) n1 + bits]
							: 0);
				ans += lower_bound(arr, 0, arr.length, w - sum + 1);
			}
			System.out.println(ans);
		}
	}
}
