# Effective STL 50条有效使用STL的经验

[TOC]

## 容器

### 慎重选择容器类型

- 序列容器：`array`、`vector`、`deque`、`forward_list`、`list`
- 关联容器
  - 有序：`set`、`map`、`multiset`、`multimap`
  - 无序：`unordered_set`、`unordered_map`、`unordered_multiset`、`unordered_multimap`

- 容器适配器：`stack`、`queue`、`priority_queue`

:sun_with_face: [more detail](https://en.cppreference.com/w/cpp/container)

### 不要试图编写独立于容器类型的代码

序列容器才支持`push_front`和`push_back`；关联容器才支持`count`、`lower_bound`、`upper_bound`、`equal_range`。

使用类型重定义`typedef`可以让我们少些很多代码。

### 确保容器中的对象拷贝正确而高效

容器中的对象尽量使用**智能指针**包含，这样做有两个好处，一，可以减少不必要的拷贝，复制；二，可以使用**多态**（存储基类的智能指针）。

### 调用`empty`而不是检查`size()`是否为0

`empty`的时间复杂度总是$O(1)$，而`size()`有时候要遍历区间才能获得。

### 区间成员函数优先于与之对应的单元素成员函数

对于所有的序列容器，都有一个成员函数`assign`，赋值。

> 给定`v1`和`v2`两个向量，使得`v1`的内容和`v2`的后半部分相同的最简单操作是什么？

```cpp
// answer
v1.assign(v2.begin() + v2.size() / 2, v2.end());
```

- 使用区间成员函数，通常可以少写代码
- 使用区间成员函数通常会得到意图清晰和更加直接的代码
- 更高的效率

区间`insert`也是推荐使用的，尽量一步到位，不要搞多次操作。

支持区间操作的成员函数：

- 区间创建：构造函数
- 区间插入：`insert`
- 区间删除：`erase`
- 区间赋值：`assign`

### 当心C++编译器最烦人的分析机制

```cpp
int f(double d);			// 声明函数f
int f(double (d));			// 声明函数f，参数两边的括号是多余的，会被忽略
int f(double);				// 声明函数f，省略参数名

int g(double (*pf)());		// 声明函数g，参数是一个函数指针
int g(double pf());			// 声明函数g，参数是一个函数指针
int g(double ());			// 声明函数g，参数是一个函数指针
```

C++编译器编译时对语句会尽量解释成**函数声明**。

```cpp
std::ifstream dataFile("ints.dat");
std::vector<int> data(std::istream_iterator<int>(dataFile), std::istream_iterator<int>());
std::sort(data.begin(), data.end());	// error: request for member ‘begin’ in ‘data’, which is of non-class type ‘std::vector<int>(std::istream_iterator<int>, std::istream_iterator<int> (*)())’	
```

上述代码是通不过编译的，编译器把`data`看成了函数声明，这个函数有两个参数

- 第一个参数的名称是`dataFile`，这个参数的类型是`std::istream_iterator<int>`；
- 第二个参数是个函数指针。

给**第一个参数加上一对括号**可以解决这个错误。

### 如果容器中包含了通过`new`操作创建的指针，切记在容器对象析构前将指针`delete`掉

这个问题同[确保容器中的对象拷贝正确而高效](###确保容器中的对象拷贝正确而高效)，用智能指针就完事了。

### ~~切勿创建包含`auto_ptr`的容器对象~~

### 慎重选择删除元素的方法

- 要删除容器中有特定值的所有对象
  - 如果容器是`vector`、`string`或`deque`，则使用`std::erase(std::remove(std::begin, std::end(), value), std::end())`；
  - 如果容器是`list`，则使用`list::remove`;
  - 如果容器是关联容器，则使用它的`erase`成员函数。
- 要删除容器中满足特定判别式的所有对象
  - 如果容器是`vector`、`string`或`deque`，则使用`std::erase(std::remove_if(std::begin, std::end(), ped), std::end())`；
  - 如果容器是`list`，则使用`list::remove_if`;
  - 如果容器是关联容器，则使用`remove_copy_if`和`swap`，或则写一个循环来遍历容器中的元素，记住要对迭代器做**后缀递增**。
- 要在循环内部做某些操作（循环删除）
  - 如果容器是序列容器：循环遍历容器，每次调用`erase`时，要用它的返回值更新迭代器；
  - 如果容器是关联容器：循环遍历容器，当把迭代器传递给`erase`时，**要对迭代器做后缀递增**（避免迭代器失效）

### 了解分配子（`allocator`）的约定和限制

