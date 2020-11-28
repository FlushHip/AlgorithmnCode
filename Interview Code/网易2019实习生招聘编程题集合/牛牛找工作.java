import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static int upper_bound(Pair[] arr, int begin, int end, int tag) {
		--begin;
		--end;
		while (begin < end) {
			int mid = (begin + end + 1) / 2;
			if (arr[mid].first > tag)
				end = mid - 1;
			else
				begin = mid;
		}
		return end + 1;
	}

	public static void main(String[] args) {
		while (cin.hasNext()) {
			int n = cin.nextInt(), m = cin.nextInt();
			Pair[] arr = new Pair[n];
			for (int i = 0; i < n; i++)
				arr[i] = new Pair(cin.nextInt(), cin.nextInt());
			Arrays.sort(arr, new Comparator<Pair>() {
				@Override
				public int compare(Pair arg0, Pair arg1) {
					return arg0.first - arg1.first;
				}
			});
			int[] ans = new int[n];
			ans[0] = arr[0].second;
			for (int i = 1; i < arr.length; ans[i] = Math.max(ans[i - 1],
					arr[i].second), ++i) {
			}
			while (m-- > 0) {
				int index = upper_bound(arr, 0, arr.length, cin.nextInt());
				System.out.println(index == 0 ? 0 : ans[index - 1]);
			}
		}
	}
}

class Pair {
	public int first;
	public int second;

	Pair() {
	}

	Pair(int first, int second) {
		this.first = first;
		this.second = second;
	}
}
