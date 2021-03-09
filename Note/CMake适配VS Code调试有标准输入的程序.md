本文的背景是使用[CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)来调试带有标准输入的程序，遇到的问题是CMake Tools目前不能提供一个额外的输入窗口来进行输入，这是目前这个插件的缺陷。

目前我解决这个问题的方式是适用`freopen`来重定向输入到文件。利用条件编译在CMake中添加对应的宏。但是这样会在代码中引入一些不起作用的代码，不美观，不过也是没有办法的事。

项目结构如下所示：

```bash
FlushHip E:\experimentlab\..\..\L6.12 git: master ≣ +0 ~2 -0 ! ❯❯❯ ls

    目录: E:\experimentlab\yz\Math\L6.12

Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----          2021/3/9     16:30            588 CMakeLists.txt
-a----         2021/2/22     22:50            101 in.dat
-a----          2021/3/9     22:52           1888 main.cpp
```

`main.cpp`：

```cpp
#include <iostream>
#include <vector>
#include <cassert>

// ...

int main(int argc, char **argv)
{
#ifdef VSCODE_CMAKE_TOOLS_DEBUG
    (void)std::freopen("in.dat", "r", stdin);
#endif

// ...
    
    return 0;
}
```

`CMakeLists.txt`：

```cmake
file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

set(TARGET_NAME main)

add_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_definitions(${TARGET_NAME} PRIVATE VSCODE_CMAKE_TOOLS_DEBUG)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
    ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat $<TARGET_FILE_DIR:${TARGET_NAME}>/
    COMMENT "copy in.dat for freopen to debug stdin")

# 禁用下freopen产生的警告
target_compile_options(${TARGET_NAME} PRIVATE $<IF:$<CXX_COMPILER_ID:MSVC>,/wd4996,-Wno-deprecated-declarations>)
```

这样就没啥问题了，如果你是使用CMake来生成Visual Studio的项目，然后调试是在Visual Studio中调试，然后你也想调试的时候重定向输入到文件，CMake可以设置Visual Studio的**调试输入参数**来避免在代码中加入无关代码。

```cmake
# 不需要add_custom_command那一行了

# 命令行的重定向输入
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "< \"${CMAKE_CURRENT_SOURCE_DIR}/in.dat\"")
```

