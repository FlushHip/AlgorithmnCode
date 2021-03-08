首先，如果是C语言，需要确定是否安装了`gcc-multilib`；如果是C++，需要确定是否安装了`g++-multilib`。假设Linux平台是Ubuntu发行版，使用C++。

```bash
sudo apt install g++-multilib
```

然后就是对CMake的设置了。

这里分为两个部分，对整个CMake项目设置，对单个Target设置。

## 对单个Target

```cmake
target_compile_options(${TARGET_NAME} PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)
target_link_options(${TARGET_NAME} PUBLIC $<$<PLATFORM_ID:Linux>:-m32>)
```

为啥**限定**是`PUBLIC`呢？因为Target有可能是动态库或者静态库，使用`PUBLIC`限定符可以使得这些选项传递到可执行文件上，毕竟32位的库也只能是32位的可执行文件使用。

## 对整个CMake项目

简单粗暴一点就是：(不知道有没有啥副作用，反正官方是没有给出这种方式，纯属民间科学)

```cmake
set(CMAKE_CXX_FLAGS -m32)
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -m32")
set(CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -m32")
set(CMAKE_MODULE_LINKER_FLAGS  "${CMAKE_MODULE_LINKER_FLAGS} -m32")
```

优雅点就是利用一个[Interface Libraries](https://cmake.org/cmake/help/v3.12/manual/cmake-buildsystem.7.html#id37)。

```cmake
add_library(32bits-build INTERFACE)
target_compile_options(32bits-build INTERFACE $<$<PLATFORM_ID:Linux>:-m32>)
target_link_options(32bits-build INTERFACE $<$<PLATFORM_ID:Linux>:-m32>)

add_library(lib SHARED lib.cpp)
target_link_libraries(lib PUBLIC 32bits-build)

add_executable(main1 main1.cpp)
target_link_libraries(main PRIVATE 32bits-build)

add_executable(main2 main2.cpp)
target_link_libraries(main PRIVATE lib)
# ...
```

