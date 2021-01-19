# Effective C++

## 让自己习惯C++

- C
- Object-Oriented C++
- TMP
- STL

### 尽量以`const`，`enum`，`inline`替换#define

**宁可以编译器替换预处理器**

预处理器定义的宏的名字进不了**符号表**，程序出错，排查调试会变得困难，错误信息非常具有迷惑性

类的静态常量（整数类型，专属常量），**是可以只声明，不定义的**，而且，初值要在声明时就给出；如果需要给出定义，那么初始化只能发生在声明时或者定义时，否则会出现重定义多重初始化的错误。

```c++
class A {
private:
    static const int kConst = 10;
    // enum { kConst = 10 };
    int arr[kConst];
};

const int A::kConst;	// 可有可无
```

如果不想别人获取类的常量 指针或者应用，可以用类内的`enum`来规避

宏函数要避免，第一，宏函数书写复杂，参数都必须加上括号；第二，宏函数的参数如果带有操作，那么这个操作可能被执行多次；第三，宏函数不利于调试，使用`inline`函数替代宏函数。

### 尽可能使用`const`

`const`可以作用于指针自身，指针所指之物。

| `char greeting[] = "hello"`; | `const data`                       | `non-const data`             |
| ---------------------------- | ---------------------------------- | ---------------------------- |
| `const pointer`              | `const char * const p = greeting;` | `char * const p = greeting;` |
| `non-const pointer`          | `const char *p = greeting;`        | `char *p = greeting;`        |

`const`作用于STL中的迭代器

```c++
const auto it = std::vector<int>::iterator{};	// T * const
auto it = std::vector<int>::const_iterator{};	// const T *
```

