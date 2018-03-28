import java.util.*;

public class Main {

	public static Scanner cin = new Scanner(System.in);

	public static int lower_bound(int[] arr, int begin, int end, int tag) {
		while (begin < end) {
			int mid = (begin + end) / 2;
			if (arr[mid] < tag)
				begin = mid + 1;
			else
				end = mid;
		}
		return begin;
	}

	public static boolean judge(Rect rect, int x, int y) {
		return rect.x[0] < x && x < rect.x[2] && rect.x[1] < y && y < rect.x[3];
	}

	public static void main(String[] args) {
		while (cin.hasNext()) {
			int n = cin.nextInt();
			Rect[] rects = new Rect[n];
			int[] approch_x = new int[n << 1], approch_y = new int[n << 1];
			for (int i = 0; i < n; rects[i++] = new Rect()) {
			}

			for (int i = 0; i < n; approch_x[i] = rects[i].x[0] = cin.nextInt(), ++i) {
			}
			for (int i = 0; i < n; approch_y[i] = rects[i].x[1] = cin.nextInt(), ++i) {
			}
			for (int i = 0; i < n; approch_x[n + i] = rects[i].x[2] = cin.nextInt(), ++i) {
			}
			for (int i = 0; i < n; approch_y[n + i] = rects[i].x[3] = cin.nextInt(), ++i) {
			}
			Arrays.sort(approch_x);
			Arrays.sort(approch_y);
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < 4; j++) {
					if (j % 2 == 0)
						rects[i].x[j] = 2 * lower_bound(approch_x, 0, n << 1,
								rects[i].x[j]);
					else
						rects[i].x[j] = 2 * lower_bound(approch_y, 0, n << 1,
								rects[i].x[j]);
				}
			}
			int col = 2 * lower_bound(approch_x, 0, n << 1,
					approch_x[2 * n - 1]);
			int row = 2 * lower_bound(approch_y, 0, n << 1,
					approch_y[2 * n - 1]);

			int ans = 1;
			for (int i = 0; i + 2 < row; i += 2) {
				for (int j = 0; j + 2 < col; j += 2) {
					int sum = 0;
					for (int k = 0; k < n; k++)
						sum += judge(rects[k], i + 1, j + 1) ? 1 : 0;
					ans = Math.max(ans, sum);
				}
			}
			System.out.println(ans);
		}
	}
}

class Rect {
	int[] x;

	Rect() {
		x = new int[4];
	}
}
