# CSDN：[招商银行信用卡2018春季招聘研发(第一批)编程题 - 题解](https://blog.csdn.net/FlushHip/article/details/79751082)

招商银行信用卡的题难度一般，基本都能做出来，因此，解析就写得简单些了。而且题中没有给出数据范围，说明数据不会很大，因此这三个题都可以暴力求解。

# 第一题

## 题目
> 给出一个非空字符串，判断这个字符串是否是由它的一个子串多次首尾拼接构成的。

## 输入描述
> 非空字符串

## 输出描述
> 如果字符串满足上述条件，则输出最长的满足条件的子串；如果不满足条件，则输出`false`。

## 样例

<pre>
<b>in:</b>
abcabc

<b>out:</b>
abc
</pre>

## 解析

枚举子串的长度，从串长减一枚举到一，然后在数组中循环判断就行了，核心代码：

```
str.charAt(i) == str.charAt(i % ans)
```

## 代码
```Java
import java.util.*;

public class Main {

	public Scanner cin = new Scanner(System.in);

	Main() {
		while (cin.hasNext()) {
			String str = cin.next();
			int ans = str.length() - 1;
			for (int i = 0; ans > 0; ans--) {
				for (i = 0; str.length() % ans == 0 && i < str.length()
						&& str.charAt(i) == str.charAt(i % ans); i++) {
				}
				if (i == str.length())
					break;
			}
			System.out.println(ans != 0 ? str.substring(0, ans) : "false");
		}
	}

	public static void main(String[] args) {
		new Main();
	}
}

```

# 第二题

## 题目
> 题目别人没给我拍全，但是我知道这是一道LeetCode的原题，LeetCode现在有中国版的了，给出中国版的链接，即[LeetCode - 22](https://leetcode-cn.com/problems/generate-parentheses/description/)。

## 输入描述
> 输入为1个正整数

## 输出描述
> 输出为所有合法的字符串，用英文逗号隔开

## 样例

<pre>
<b>in:</b>
2

<b>out:</b>
(()),()()
</pre>

## 解析

先给出在LeetCode上通过的代码：

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        this->n = n;
        vector<string> ret;
        dfs(0, 0, 0, "", ret);
        return ret;
    }
private:
    int n;
    void dfs(int x, int l, int r, string str, vector<string> &ret)
    {
        if (x == 2 * n) {
            ret.push_back(str);
            return ;
        }
        if (l < n)
            dfs(x + 1, l + 1, r, str + "(", ret);
        if (r < n && l > r)
            dfs(x + 1, l, r + 1, str + ")", ret);
    }
};
```

给出一个整数`n`，那么生成的合法括号串的长度是`2 * n`，那么运用递归去枚举每个位置上的可能出现的字符`(`，`)`，枚举的时候要注意，当前位置可以放`(`，但是能不能放`)`就要看到目前为止放了多少个`)`，如果`(`的个数比`)`多，那么当前位置就可以放`)`，这其实和用栈验证括号串的合法性的思想是一样的。

## 代码
```Java
import java.util.*;

public class Main {

	public Scanner cin = new Scanner(System.in);
	
	public int n;
	public ArrayList<String> ans = new ArrayList<String>();
	
	public void dfs(int x, int l, int r, String str) {
		if (x == 2 * n) {
			ans.add(str);
			return ;
		}
		if (l < n)
			dfs(x + 1, l + 1, r, str + "(");
		if (r < n && l > r)
			dfs(x + 1, l, r + 1, str + ")");
	}

	Main() {
		while (cin.hasNext()) {
			n = cin.nextInt();
			ans.clear();
			dfs(0, 0, 0, "");
			for (int i = 0; i < ans.size(); i++)
				System.out.print(ans.get(i) + (i != ans.size() - 1 ? "," : "\n"));
		}
	}

	public static void main(String[] args) {
		new Main();
	}
}

```

# 第三题

## 题目
> 给出一个整数`n`，将`n`分解成至少两个整数之和，使得这些整数的乘积最大化，输出能获得的最大的乘积。

## 输入描述
> 输入为一个整数

## 输出描述
> 输出为一个整数

## 样例

<pre>
<b>in:</b>
10

<b>out:</b>
36
</pre>

## 解析

这个题还是要一丁点数学知识的，给你一个数`n = a + b`，`a * b`何时最大，那必然是`a`和`b`尽量靠近时才最大，现在这个`n`可以分解成多个数字相加，那么这些数字相乘什么时候最大呢，和两个数字一样，这些数字肯定也是都靠在一起才最大，什么叫靠在一起呢，就是任意两个数只差的绝对值小于等于1，那么这些数字必然可以分解成`x, x, x, ...,x + 1, x + 1, ...`这种形式。这么一想，这个代码就好写了，枚举其中的从1到`n / 2`枚举`x`，先看看可以分解成多少个数字，结果是`n / x`，还剩下`n % x`，把`n % x`一个一个分配到之前的`x`中，这里要特别注意，`n % x`有可能大于`n / x`，这说明，把`n % x`分配完，还有剩下的，不符合要求，而且这种情况肯定会在枚举`x = x + 1`时会处理，因此过滤掉这种`x`就行了。

## 代码
```Java
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

```
