**原题链接：**[点这儿](https://www.nowcoder.com/test/9763997/summary)。

网易的题还是有技术含量的，二分和数学和优美暴力考察得较多，这些东西在工作中确实很重要，都是优化程序的方法。


# 第一题：牛牛找工作

## 题目：
> 为了找到自己满意的工作，牛牛收集了每种工作的难度和报酬。牛牛选工作的标准是在难度不超过自身能力值的情况下，牛牛选择报酬最高的工作。在牛牛选定了自己的工作后，牛牛的小伙伴们来找牛牛帮忙选工作，牛牛依然使用自己的标准来帮助小伙伴们。牛牛的小伙伴太多了，于是他只好把这个任务交给了你。

## 输入描述：
> 每个输入包含一个测试用例。
每个测试用例的第一行包含两个正整数，分别表示工作的数量$N(N\le100000)$和小伙伴的数量$M(M\le100000)$。
接下来的`N`行每行包含两个正整数，分别表示该项工作的难度$D_i(D_i\le1000000000)$和报酬$P_i(P_i\le1000000000)$。
接下来的一行包含`M`个正整数，分别表示`M`个小伙伴的能力值$A_i(A_i\le1000000000)$。
保证不存在两项工作的报酬相同。


## 输出描述：
> 对于每个小伙伴，在单独的一行输出一个正整数表示他能得到的最高报酬。一个工作可以被多个人选择。

## 样例：
<pre>
<b>in:</b>
3 3 
1 100 
10 1000 
1000000000 1001 
9 10 1000000000

<b>out:</b>
100 
1000 
1001
</pre>

## 解析：

`N， M`都达到了$10^5$，很明显，对于每次询问要采用$O(logn)$或$O(1)$的算法，$O(logn)$可以二分查找，$O(1)$可以通过预处理来达到目标。

因此，先按每个工作的能力值升序排序，这样子可以二分查找到每个同学能做的所有工作，然后再这些工作中找到薪酬最大的；

如何快速找薪酬最大的，这里就要对刚刚升序排序的输出进行区间最大值的预处理了，递推一下就可以得到`[1, i]`区间的最大值，找区间薪酬最大，只需要访问下`dp[i]`就行了。

## 代码：

```
# include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int n, m; cin >> n >> m; ) {
        vector<pair<int, int> > arr;
        for (int i = 0, d, p; i < n; cin >> d >> p, arr.emplace_back(d, p), i++) {}
        sort(arr.begin(), arr.end());
        vector<int> ans(n);
        ans[0] = arr[0].second;
        for (int i = 1; i < (int)arr.size(); ans[i] = max(ans[i - 1], arr[i].second), ++i) {}

        for (int x; m--; ) {
            cin >> x;
            cout << ans[upper_bound(arr.begin(), arr.end(), make_pair(x, 0x3f3f3f3f)) - 1 - arr.begin()] << endl;
        }
    }
    return 0;
}

```

# 第二题：被3整除

## 题目：
> 小Q得到一个神奇的数列: `1, 12, 123,...12345678910,1234567891011...`。
并且小Q对于能否被`3`整除这个性质很感兴趣。
小Q现在希望你能帮他计算一下从数列的第`l`个到第`r`个(包含端点)有多少个数可以被`3`整除。

## 输入描述：
> 输入包括两个整数`l`和`r`$(1 <= l <= r <= 10^9)$, 表示要求解的区间两端。


## 输出描述：
> 输出一个整数, 表示区间内能被3整除的数字个数。

## 样例：
<pre>
<b>in:</b>
2 5

<b>out:</b>
3
</pre>

## 解析：

 看到数据范围就应该明白，这题不能递推，一是数组开不了这么大，二是递推时间很长。因此只能用数学方法算出来(这就是数据范围给我们做题的提示)。

一个数字`n`如果可以被`3`整除，$n = a * 10^n + b$，那么$a \% 3 + b \% 3 = 0$，`1, 2, 3, 4, ...`分别对3取模得到`1, 2, 0, 1, 2, 0, ...`，这个时候再看题中给出的序列，`1, 12, 123, 1234, ...`是不是可以把其中元素分解成$n = a * 10^n + b$，那么可以发现，`1, 12, 123, 1234, 12345, ...`，能被3整除的如下`false, true, true, false, true, true, false, ...`，可以发现这个序列以`3`为周期，因此，代码就可以写出来了。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

int fun(int x)
{
    return x / 3 * 2 + (x % 3 == 0 ? 0 : x % 3 == 1 ? 0 : 1);
}

int main()
{
    for (int l, r; cin >> l >> r; cout << fun(r) - fun(l - 1) << endl) {}
    return 0;
}

```

# 第三题：安置路灯

## 题目：
> 小Q正在给一条长度为`n`的道路设计路灯安置方案。
为了让问题更简单,小Q把道路视为`n`个方格,需要照亮的地方用`'.'`表示, 不需要照亮的障碍物格子用`'X'`表示。
小Q现在要在道路上设置一些路灯, 对于安置在`pos`位置的路灯, 这盏路灯可以照亮`pos - 1, pos, pos + 1`这三个位置。
小Q希望能安置尽量少的路灯照亮所有`'.'`区域, 希望你能帮他计算一下最少需要多少盏路灯。



## 输入描述：
> 输入的第一行包含一个正整数`t`$(1 \le t \le 1000)$, 表示测试用例数
接下来每两行一个测试数据, 第一行一个正整数`n`$(1 \le n \le 1000)$,表示道路的长度。
第二行一个字符串`s`表示道路的构造,只包含`'.'`和`'X'`。


## 输出描述：
> 对于每个测试用例, 输出一个正整数表示最少需要多少盏路灯。

## 样例：
<pre>
<b>in:</b>
2
3
.X.
11
...XX....XX

<b>out:</b>
1
3
</pre>

## 解析：

一开始，我以为障碍物是不能放灯的，故，只要求出连续的`.`有多少个`.`(假设`sum`个)，答案就是`ceil(sum / 3)`，于是写出了下面的代码；

```
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	for (cin >> T; T--; ) {
		int n, ans = 0;
		string str;
		cin >> n >> str;
        for (auto it = str.begin(), pre = it; it != str.end(); ) {
			for (; it != str.end() && *it == 'X'; ++it) {}
			for (pre = it; it != str.end() && *it == '.'; ++it) {}
			ans += ceil((it - pre + 0.0) / 3);
        }
        cout << ans << endl;
	}
	return 0;
}

```

这个题，障碍物是可以放灯的，那么，贪心来搞，首先，对于`...`来说，我们把灯放在第二个位置上是绝对优于把灯放在第一个位置上的，如果发现当前点是障碍物，不要管它，继续向后走，然后按找上面所说的放灯就行了。


## 代码：

```
#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	for (cin >> T; T--; ) {
		int n, ans = 0;
		string str;
		cin >> n >> str;
        for (int i = 0; i < (int)str.size(); ) {
			for (; i < (int)str.size() && str[i] == 'X'; ++i) {}
			for (; i < (int)str.size() && str[i] == '.'; ans++, i += 3) {}
        }
        cout << ans << endl;
	}
	return 0;
}

```

# 第四题：数对

## 题目：
> 牛牛以前在老师那里得到了一个正整数数对`(x, y)`, 牛牛忘记他们具体是多少了。
但是牛牛记得老师告诉过他`x`和`y`均不大于`n`, 并且`x`除以`y`的余数大于等于`k`。
牛牛希望你能帮他计算一共有多少个可能的数对。




## 输入描述：
> 输入包括两个正整数`n,k`$(1 \le n \le 10^5, 0 \le k \le n - 1)$。

## 输出描述：
> 对于每个测试用例, 输出一个正整数表示可能的数对数量。

## 样例：
<pre>
<b>in:</b>
5 2

<b>out:</b>
7
</pre>

## 解析：

这里我们从`k + 1`枚举`y`到`n`，对于一个确定的`y`，`x % y`的值的大小是有周期性的，因此可以直接计算出来，但是对于`k = 0`要特殊处理，因为对于任意的`(x, y)`，`x % y`永远大于等于0，因此，当`k = 0`时，答案为`n * n`。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    for (LL n, k; cin >> n >> k; ) {
        LL ans = 0;
        if (!k)
            ans = n * n;
        else
            for (LL y = k + 1; y <= n; y++)
                ans += n / y * (y - k) + (n % y >= k ? n % y - k + 1 : 0);
        cout << ans << endl;
    }
    return 0;
}

```
# 第五题：矩形重叠

## 题目：
> 平面内有`n`个矩形, 第`i`个矩形的左下角坐标为$(x1[i], y1[i])$, 右上角坐标为$(x2[i], y2[i])$。
如果两个或者多个矩形有公共区域则认为它们是相互重叠的(**不考虑边界和角落**)。
请你计算出平面内重叠矩形数量最多的地方,有多少个矩形相互重叠。


## 输入描述：
> 输入包括五行。
第一行包括一个整数`n`$(2 \le n \le 50)$, 表示矩形的个数。
第二行包括`n`个整数$x_1[i](-10^9 \le x_1[i] \le 10^9)$,表示左下角的横坐标。
第三行包括`n`个整数$y_1[i](-10^9 \le y_1[i] \le 10^9)$,表示左下角的纵坐标。
第四行包括`n`个整数$x_2[i](-10^9 \le x_2[i] \le 10^9)$,表示右上角的横坐标。
第五行包括`n`个整数$y_2[i](-10^9 \le y_2[i] \le 10^9)$,表示右上角的纵坐标。


## 输出描述：
> 输出一个正整数, 表示最多的地方有多少个矩形相互重叠,如果矩形都不互相重叠,输出1。

## 样例：
<pre>
<b>in:</b>
2
0 90
0 90
100 200
100 200

<b>out:</b>
2
</pre>

## 解析：

这个题和线段重叠那个题很像，但是多了一维就不是那么好搞了，这里的`n`很小，那么肯定就是从这里下手了；

我的第一反应就是随机化算法，即随机生成一个点，然后判断这个点在多少个矩形中，维护一个最大值。但是坐标的范围太大了，因此，要进行离散化，把X轴和Y轴的坐标离散化成小坐标；

但是，这个离散化算法还是有问题，无法处理两个矩形共线或共点！多么希望我们随机化出来的点不在矩形的边界上啊；

注意到，我们离散化出来的坐标都是挨在一起的，例如`1`后面一定是`2`，但是如果我们把离散化后的坐标扩大两倍，那么`2`后面就是`4`了，中间的`3`是没有使用的，而**单位区域的中心是不会在矩形的边界上的**，因此我们可以随机化单位区域的中心，以这个点去判断是否在矩形中，这样就解决了**不考虑边界和角落**这个条件，而把离散化后的坐标扩大两倍，举个例子，中心就是`(2 + 4) / 2 = 3`，中心可以确保都是正整数。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x[4];
    Rect() {}
};

bool judge(const vector<Rect>::iterator &it, int x, int y)
{
    return it->x[0] < x && x < it->x[2] && it->x[1] < y && y < it->x[3];
}

int main()
{
    for (int n; cin >> n; ) {
        vector<Rect> rects(n);
        vector<int> approch_x, approch_y;
        for (int i = 0, x; i < n; cin >> x, approch_x.push_back(rects[i++].x[0] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_y.push_back(rects[i++].x[1] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_x.push_back(rects[i++].x[2] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_y.push_back(rects[i++].x[3] = x)) {}
        sort(approch_x.begin(), approch_x.end());
        sort(approch_y.begin(), approch_y.end());
        for (auto it = rects.begin(); it != rects.end(); ++it) {
            for (int i = 0; i < 4; i++) {
                if (i % 2 == 0)
                    it->x[i] = (lower_bound(approch_x.begin(), approch_x.end(), it->x[i]) - approch_x.begin()) * 2;
                else
                    it->x[i] = (lower_bound(approch_y.begin(), approch_y.end(), it->x[i]) - approch_y.begin()) * 2;
            }
        }

        int col = (lower_bound(approch_x.begin(), approch_x.end(), approch_x.back()) - approch_x.begin()) * 2;
        int row = (lower_bound(approch_y.begin(), approch_y.end(), approch_y.back()) - approch_y.begin()) * 2;

        int ans = 1;
        for (int i = 0; i + 2 < row; i += 2) {
            for (int j = 0; j + 2 < col; j += 2) {
                int sum = 0;
                for (auto it = rects.begin(); it != rects.end(); ++it)
                    sum += judge(it, i + 1, j + 1);
                ans = max(ans, sum);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

```

# 第六题：迷路的牛牛

## 题目：
> 牛牛去犇犇老师家补课，出门的时候面向北方，但是现在他迷路了。虽然他手里有一张地图，但是他需要知道自己面向哪个方向，请你帮帮他。 


## 输入描述：
> 每个输入包含一个测试用例。
每个测试用例的第一行包含一个正整数，表示转方向的次数`N`$(N\le1000)$。
接下来的一行包含一个长度为`N`的字符串，由`L`和`R`组成，`L`表示向左转，`R`表示向右转。



## 输出描述：
> 输出牛牛最后面向的方向，`N`表示北，`S`表示南，`E`表示东，`W`表示西。

## 样例：
<pre>
<b>in:</b>
3
LRR

<b>out:</b>
E
</pre>

## 解析：

如图：
![这里写图片描述](https://img-blog.csdn.net/2018032816472251?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0ZsdXNoSGlw/font)

把`NESW`用数字`0123`表示，向左走就减一，向右走就加一，由于在处理的过程中`ans`可能为负数，因此对`ans`加`4`再模`4`。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

int main()
{
	const char DIR[] = "NESW";
	for (int n; cin >> n; ) {
		string str;
		cin >> str;
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans = (ans + (str[i] == 'L' ? -1 : 1) + 4) % 4;
		cout << DIR[ans % 4] << endl;
	}
	return 0;
}

```

# 第七题：牛牛的闹钟

## 题目：
> 牛牛总是睡过头，所以他定了很多闹钟，只有在闹钟响的时候他才会醒过来并且决定起不起床。从他起床算起他需要`X`分钟到达教室，上课时间为当天的`A`时`B`分，请问他最晚可以什么时间起床 


## 输入描述：
> 每个输入包含一个测试用例。
每个测试用例的第一行包含一个正整数，表示闹钟的数量`N`$(N\le100)$。
接下来的`N`行每行包含两个整数，表示这个闹钟响起的时间为$H_i(0\le A<24)时M_i(0\le B<60)$分。
接下来的一行包含一个整数，表示从起床算起他需要$X(0\le X\le100)$分钟到达教室。
接下来的一行包含两个整数，表示上课时间为$A(0\le A<24)$时$B(0\le B<60)$分。
数据保证至少有一个闹钟可以让牛牛及时到达教室。


## 输出描述：
> 输出两个整数表示牛牛最晚起床时间。

## 样例：
<pre>
<b>in:</b>
3 
5 0 
6 0 
7 0 
59 
6 59

<b>out:</b>
6 0
</pre>

## 解析：

把时间全都化成分钟，然后算出牛牛最迟起床时间，在闹钟的时间中二分求上界就行了。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int n; cin >> n; ) {
        vector<int> arr;
        for (int i = 0, x, y; i < n; cin >> x >> y, arr.push_back(x * 60 + y), ++i) {}
        sort(arr.begin(), arr.end());
        int x, A, B;
        cin >> x >> A >> B;
        int ans = *(lower_bound(arr.begin(), arr.end(), A * 60 + B - x + 1) - 1);
        cout << ans / 60 << " " << ans % 60 << endl;
    }
    return 0;
}

```

# 第八题：牛牛的背包问题

## 题目：
> 牛牛准备参加学校组织的春游, 出发前牛牛准备往背包里装入一些零食, 牛牛的背包容量为`w`。
牛牛家里一共有`n`袋零食, 第`i`袋零食体积为`v[i]`。
牛牛想知道在总体积不超过背包容量的情况下,他一共有多少种零食放法(总体积为`0`也算一种放法)。


## 输入描述：
> 输入包括两行
第一行为两个正整数`n`和`w`$(1 \le n \le 30, 1 \le w \le 2 * 10^9)$,表示零食的数量和背包的容量。
第二行`n`个正整数`v[i]`$(0 \le v[i] \le 10^9)$,表示每袋零食的体积。


## 输出描述：
> 输出一个正整数, 表示牛牛一共有多少种零食放法。

## 样例：
<pre>
<b>in:</b>
3 10
1 2 4

<b>out:</b>
8
</pre>

## 解析：

一看就是最经典“0 - 1背包问题“，但是，背包的容量太大了，会导致数组都开不了，而且还超时。

那么，就枚举呗，枚举使用二进制位运算枚举集合，就写了以下的代码：

```
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
	for (LL n, w; cin >> n >> w; ) {
		vector<LL> v;
		for (int i = 0, x; i < n; cin >> x, v.push_back(x), ++i) {}
		LL ans = 0;
        for (int i = 0; i < (1 << n); i++) {
			LL sum = 0;
			for (int bit = 0; bit < n; bit++)
				sum += (i & (1 << bit)) ? v[bit] : 0;
			ans += sum <= w;
        }
        cout << ans << endl;
	}
	return 0;
}

```

写完之后才意识到$2^{30} \approx 10^9 $，GG，这肯定不行，不过枚举还是必要的，毕竟不能动态规划了，那就少枚举点吧，枚举一半，一半是$2^{15} \approx 10^5$，好像可以，那另一半怎么办，我们可以把第一半枚举出来的和存到数组`arr`中，然后排序，这样，在枚举另一半的时候可以通过`w`减去枚举得到的值，结果假设为`res`，最后利用这个`res`在`arr`中二分求上界就可以得到当前状态的答案，维护一个和，这个题就通过了。

## 代码：

```
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    for (LL n, w; cin >> n >> w; ) {
        vector<LL> v;
        for (int i = 0, x; i < n; cin >> x, v.push_back(x), ++i) {}

        LL n1 = n >> 1, n2 = n - n1;

        vector<LL> arr;
        for (int i = 0; i < (1 << n1); i++) {
            LL sum = 0;
            for (int bits = 0; bits < n1; bits++)
                sum += (i & (1 << bits)) ? v[bits] : 0;
            arr.push_back(sum);
        }
        sort(arr.begin(), arr.end());

        LL ans = 0;
        for (int i = 0; i < (1 << n2); i++) {
            LL sum = 0;
            for (int bits = 0; bits < n2; bits++)
                sum += (i & (1 << bits)) ? v[n1 + bits] : 0;
            ans += lower_bound(arr.begin(), arr.end(), w - sum + 1) - arr.begin();
        }
        cout << ans << endl;
    }
    return 0;
}

```

# 代码JAVA实现

JAVA的代码和C++的代码差不多，最大的区别就是JAVA中没有`lower_bound`，`upper_bound`，这是STL中的两个二分求上下界函数，自己手动实现一下就好了，可以参考[你真的理解二分的写法吗 - 二分写法详解](https://blog.csdn.net/flushhip/article/details/79261608)。

## 牛牛找工作

```Java
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
```

## 被3整除
```Java
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
```

## 安置路灯
```Java
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
```

## 迷路的牛牛
```Java
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
```

## 数对
```Java
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
```
## 矩形重叠
```Java
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
```

## 牛牛的闹钟
```Java
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
```

## 牛牛的背包问题
```Java
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
```
