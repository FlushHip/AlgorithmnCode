# More Effective C++ 35个改善编程与设计的有效方法

[TOC]

## 基础议题

### 仔细区别pointers和references

## 操作符

### 对定制的”类型转换函数“保持警觉

用户定制转换行为：

- 单自变量构造函数：一个参数就可以成功调用构造函数，例如只有一个参数的构造函数，==有默认值的构造函数==[^1]。

- 隐式类型转换操作符：`operator T()`。

尽量不要写隐式类型转换符，尽量写显式函数完成转换，这样意义是明确的，考虑`std::string`提供了一个显式函数`c_str`来转换成`const char *`。

避免单自变量构造函数的最好方法是`explicit`。当然，还有一条重要的定律可以避免单自变量构造函数转换，**即没有任何一个转换程序可以内含一个以上的用户定制转换行为**。

```cpp
class Array {
public:
    class ArraySize {
    public:
        ArraySize(int size) : size_() {}
        int size() const { return size_; };
    private:
        int size_;
    };
    
    Array(ArraySize size);
};

bool deal_array(const Array &array);
deal_array(10);							// error, int -> ArraySize; ArraySize -> Array
```

`ArraySize`叫做代理类，这种技术值得学习。

### 区别increment/decrement操作符的前置和后置形式



[^1]:有$n$个默认值，或者有$n-1$个默认值