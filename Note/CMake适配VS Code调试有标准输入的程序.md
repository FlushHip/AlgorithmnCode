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

# 使用Visual Studio调试默认生成的Target的工作目录是项目目录，因此要想使相对路径in.dat生效，就要修改下工作目录为exe所在目录
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)
```

上述实现不用引入其他Target，从美观上来看比较好，但是会有一个缺陷，这个缺陷是由`add_custom_command(TARGET)`的特性(如果Target已经被构建好了，则不会再重复执行生成事件)导致的，也就是说啊，如果你这个时候修改了`in.dat`中的数据，调试的时候是不会实时更新的，如果要更新，那么就要使得`main.cpp`发生一次修改，使这个Target过期。这其实是个很蛋疼的事。。。

所幸，可以通过`add_custom_command`、`add_custom_target`、`add_dependencies`联动来解决这个问题。不过就要额外引入一个*Utility*的Target。

`CMakeLists.txt`：

```cmake
file (GLOB SOURCE_FILES *.c *.cpp)
file (GLOB HEADER_FILES *.h *.hpp)

set(TARGET_NAME main)

add_executable (${TARGET_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_compile_definitions(${TARGET_NAME} PRIVATE VSCODE_CMAKE_TOOLS_DEBUG)

set(OUTPUT_AUX_DIR ${CMAKE_CURRENT_BINARY_DIR})
if (MSVC)
    set(OUTPUT_DIR_AUX ${OUTPUT_AUX_DIR}/$<CONFIG>)
endif ()

add_custom_command(OUTPUT ${OUTPUT_AUX_DIR}/in.dat
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat ${OUTPUT_AUX_DIR}
    COMMENT "copy ${CMAKE_CURRENT_SOURCE_DIR}/in.dat for freopen to debug stdin"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/in.dat
    VERBATIM)

add_custom_target(${TARGET_NAME}_AUX
    DEPENDS ${OUTPUT_AUX_DIR}/in.dat
    VERBATIM)

set_target_properties(${TARGET_NAME}_AUX PROPERTIES FOLDER "DebugAux")

add_dependencies(${TARGET_NAME} ${TARGET_NAME}_AUX)

set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)
```

这样就没啥问题了，如果你是使用CMake来生成Visual Studio的项目，然后调试是在Visual Studio中调试，然后你也想调试的时候重定向输入到文件，CMake可以设置Visual Studio的**调试输入参数**来避免在代码中加入无关代码。

```cmake
# 不需要add_custom_command那一行了

# 命令行的重定向输入
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "< \"${CMAKE_CURRENT_SOURCE_DIR}/in.dat\"")
```

