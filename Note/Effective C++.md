# Effective C++ 改善程序与设计的55个具体做法

## 让自己习惯C++

### 视C++为一个语言联邦

- C
- Object-Oriented C++
- TMP
- STL

### 尽量以`const`，`enum`，`inline`替换`#define`

**宁可以编译器替换预处理器**

预处理器定义的宏的名字进不了**符号表**，程序出错，排查调试会变得困难，错误信息非常具有迷惑性

类的静态常量（整数类型，专属常量），**是可以只声明，不定义的**，而且，初值要在声明时就给出；如果需要给出定义，那么初始化只能发生在声明时或者定义时，否则会出现重定义多重初始化的错误。

```cpp
class A {
private:
    static const int kConst = 10;
    // enum { kConst = 10 };
    int arr[kConst];
};

const int A::kConst;	// 可有可无
```

如果不想别人获取类的常量指针或者引用，可以用类内的`enum`来规避

宏函数要避免，第一，宏函数书写复杂，参数都必须加上括号；第二，宏函数的参数如果带有操作，那么这个操作可能被执行多次；第三，宏函数不利于调试，使用`inline`函数替代宏函数。

### 尽可能使用`const`

`const`可以作用于指针自身，指针所指之物。

| `char greeting[] = "hello"`; | `const data`                       | `non-const data`             |
| ---------------------------- | ---------------------------------- | ---------------------------- |
| `const pointer`              | `const char * const p = greeting;` | `char * const p = greeting;` |
| `non-const pointer`          | `const char *p = greeting;`        | `char *p = greeting;`        |

`const`作用于STL中的迭代器

```cpp
const auto it = std::vector<int>::iterator{};	// T * const
auto it = std::vector<int>::const_iterator{};	// const T *
```

`const`对于成员函数的作用，修饰成员函数可以标识这个成员函数是不可以修改对象内容的，同时，`const`修饰成员函数，`const`会成为函数签名的一部分，因此可以通过`const`来重载函数。

```cpp
class vector {
public:
    const int& operator[] (std::size_t position) const {
        return data[position];
    }
    int& operator[] (std::size_t position) {
        return data[position];
    }
private:
    enum { kLength = 10 };
    int data[kLength];
};
```

如果const和non-const的函数的实现是一样的，那么上述的方式会造成代码冗余，其实**non-const函数去调用const版本的函数一点问题都没有**。因此我们需要进行两次转型，第一把`this`转成`const this`这样才会调用重载的const版本函数；第二，把返回值的常量型手动去掉，这等于你告诉编译器：“**我知道那个变量是常量，但是对这个常量进行读写是没问题的，出了问题后果我自己负责**”。

```cpp
class vector {
public:
    const int& operator[] (std::size_t position) const {
        return data[position];
    }
    int& operator[] (std::size_t position) {
        return const_cast<int &>(							// 第一次转
            static_cast<const vector &>(*this)[position])	// 第二次转;
    }
private:
    enum { kLength = 10 };
    int data[kLength];
};
```

`mutable`可使变量在常量成员函数中修改被修饰的变量，达到灵活性。

```cpp
class vector {
public:
    size_t get_length() const {
        if (0u == length + 1)
            length_ = fun(data);	// 计算数据长度
        return length;
    }
private:
    mutable size_t length = -1;
    int *data;
}
```

### 确定对象被使用前已被初始化

对于内置类型，定义时置`0`；对于`bool`值，定义时要置`false`；对于指针，定义时要置`nullptr`，养成习惯。

要分清楚**初始化**和**赋值**的区别，尤其是类的成员变量。**Ｃ++规定，对象的成员变量初始化动作发生在进入构造函数本体之前，也就是成员初始化列表**

同时，如果成员变量是`const`或者引用，那就必须使用成员初始化列表了，这很好理解。

类的成员函数的初始化顺序：基类总是先于派生类初始化；**按照成员变量声明的顺序初始化**。

static对象：其生命周期从构造开始到程序结束，包括全局对象、定义在`namespace`内的对象、类的静态变量、函数的静态变量。

- **local static对象**：函数的静态变量，**使用时才会初始化**
- non-local static对象：除了local static对象，其余都是non-local static对象

**C++对定义于不同编译单元内的non-local static对象的初始化顺序并无明确定义**，因此如果你的某些non-local static对象之间在构造或者析构上有限制的顺序，**那么请使用函数把non-local static对象转成local static对象。这样就可以通过调用关系来确定构造和析构的顺序（先构造的后析构）**。

```cpp
vector & Vector() {
    static vector instance;
    return instance;
}
```

这其实就是**单例模式**，**C++11后，local static对象的初始化是线程安全的**。这其实是智慧的表现，因为在写C++的过程中，尝尝会在构造函数中引用一些单例，而上述单例写法恰恰就避免了对象初始化依赖的问题。

## 构造/析构/赋值运算

### 了解C++默默编写并调用哪些函数

```cpp
class Empty {};

class Empty {
public:
    Empty() {};								// default ctor
    Empty(const Empty &) {};				// copy ctor
    Empty& operator= (const Empty &) {};	// copy assignment ctor
    
    // C++11
    Empty(const Empty &&) {};				// move ctor
    Empty& operator= (const Empty &&) {};	// move assignment ctor
}
```

如果在构造或者复制的过程中存在**深拷贝**，那么就一定不能使用编译器默认生成的这些函数，因为这些函数只会执行**浅拷贝**。

同时，如果成员变量存在**引用**和**常量**，**那么编译器就不会生成默认的拷贝构造函数和拷贝赋值构造函数**。因为编译器不知道如何实现这两种类型的拷贝，必须自己手动定义。

### 若不想使用编译器自动生成的函数，就应该明确拒绝

```cpp
  struct base_token {};
  class noncopyable: base_token
  {
  protected:
#if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) && !defined(BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS)
      BOOST_CONSTEXPR noncopyable() = default;
      ~noncopyable() = default;
#else
      noncopyable() {}
      ~noncopyable() {}
#endif
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
      noncopyable( const noncopyable& ) = delete;
      noncopyable& operator=( const noncopyable& ) = delete;
#else
  private:  // emphasize the following members are private
      noncopyable( const noncopyable& );
      noncopyable& operator=( const noncopyable& );
#endif
  };
```

```cpp
#include <boost/core/noncopyable.hpp>

class Node : private boost::noncopyable {};
```

### 为多态基类声明`virtual`析构函数

如果不这么做，**虚函数的性质（多态）**决定了析构只是做到了部分析构，还是可能会有资源泄漏发生。

通常，如果一个类不含任何的虚函数，那么这个类就不太可能作为基类来继承了。如果一个类不做基类还加上`virtual`修饰函数，那么就会引入**虚函数机制，即虚指针**，这会导致类变大，且调用函数时会多一层指针解引用。

如果你确定你编写的类不会用作基类，请使用`final`进行修饰。

如果要实现一个纯虚类，但是现在这个纯虚类的接口你又没有想好，那么可以**把析构函数定义为纯虚函数，同时又提供一份空的析构函数实现**

```cpp
class InterfaceOne {
public:
    virtual ~InterfaceOne() = 0;
}

~InterfaceOne::InterfaceOne() {};
```

### 别让异常逃离析构函数

在同一作用域下，不同对象的析构是有顺序的，如果已经到了析构这一步，先析构的的对象中抛出异常，那么会导致后析构的对象的析构函数没有机会执行，这样会导致资源泄漏。

在析构函数中，对有可能发生异常的代码要进行捕获，然后**吞下**或者**结束程序**。

### 绝不在构造或者析构过程中调用`virtual`函数

**构造和析构过程之中虚函数机制失去了作用**，在基类的构造过程中，派生类还没有构造，如果这个时候调用虚函数，虚函数中使用了派生类特有的变量，那么这个行为就危险了。因此，编译器会让虚函数机制在构造和析构过程中失去作用。

```cpp
class Transaction {
public:
    Transaction() {
        log("ctro");
    }
    ~Transaction() {
        log("dtro");
    }
    virtual void log(const std::string &str) const = 0;
};

void Transaction::log(const std::string &str) const
{
    std::cout << this << " base log | " << str << std::endl;
}

class BuyTransaction : public Transaction {
public:
    BuyTransaction() = default;
    virtual void log(const std::string &str) const override;
};

void BuyTransaction::log(const std::string &str) const
{
    std::cout << this << " drived log | " << str << std::endl;
}

{
    BuyTransaction{};
}
```

### 令`operator=`返回一个reference to `*this`

```cpp
// x = y = 3; 达到这种效果

basic_ostream& operator<<(const void *val) {
    // ...
    return *this;
}
```

### 在`operator=`中处理“自我赋值”

### 复制对象时勿忘其每一个成分

如果你为class添加一个成员变量，那么你必须同时修改拷贝构造函数。

如果你为派生类编写拷贝构造函数和拷贝赋值构造函数，那么一定要调用基类对应的相关函数，切记！！！

## 资源管理

异常、函数内多重返回路径等等导致资源管理困难重重。

### 以对象管理资源

进入一个区域，对象的构造函数执行；离开区域，对象的析构函数执行。**资源取得的时机便是初始化的时机——RAII**

```cpp
std::shared_ptr;
std::unique_ptr;
std::lock_guard;
std::unique_lock;
```

### 在资源管理类中小心copying行为

- 禁止复制
- 对底层资源做引用计数
- 复制底层资源
- 转移底层资源

### 在资源管理类中提供对原始资源的访问

提供一个访问原始资源的接口，这主要是面对那些C语言的API，这样要显示调用这个接口才能获得原始资源，如果你能确定在使用裸指针的API中不会破坏资源的释放情况，那么你可以使用。

当然，也可以提供隐式转换接口，这样会比较方便客户，但是会增加程序出错的机会。

```cpp
std::shared_ptr<int>::get();

template <typename T>
class AutoPtr {
public:
    explicit AutoPtr(T* p) : ptr(p) {}
    explicit AutoPtr(nullptr_t = nullptr) {}
    operator T* () const {
        return ptr.get();
    }
private:
    std::shared_ptr<T> ptr;
};

template <typename T>
void print(const T* ptr)
{
    std::cout << ptr << std::endl;
}

{
    AutoPtr<int> ptr(new int{5});
    print<int>(ptr);
}
```

### 成对使用`new`和`delete`要采用相同形式

```cpp
std::string *stringPtr1 = new std::string;
std::string *stringPtr2 = new std::string[10];

delete stringPtr1;
delete[] stringPtr2;
```

如果对`stringPtr2`调用`delete`，那么数组对象的内存不会泄漏，而每个对象的堆内存会发生泄漏，因为，`delete`只会执行一次析构函数。

因此，不要对数组形式的变量进行`typedef`。

### 以独立语句将newed对象置入智能指针

需要保证`new`和`std::shared_ptr`构造的连续性，因此，这两部分单独成一条语句，避免其余操作因**编译器优化**而插入到这两部分之中，破坏“原子性”。如果这两部分不能连续，那么很可能就会造成资源泄漏。

```cpp
int priority();
void process(std::shared_ptr<Widget> w, int prior);

process(std::shared_ptr(new Widget), priority());
// 1. new Widget
// 2. priority() , 抛出异常，函数返回
// 3. std::shared_ptr构造，根本没有机会执行

// 解决方法
// - 1
std::shared_ptr<Widget> ptr(new Widget);
process(ptr, priority());

// - 2
process(std::make_shared<Widget>(), priority());
```

