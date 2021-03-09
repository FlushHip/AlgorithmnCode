由于Windows上不支持Linux上的共享库运行时查找机制(说的就是`rpath`或者`runpath`)。那么在Windows上，运行一个带有动态库的可执行程序的最简单方法就是把`dll`和`exe`放一起（可执行程序所在目录就是Windows查找动态库必搜索的目录之一）。

粗暴一点的方法就是把所有的CMake输出文件都放一个目录去，那么`dll`和`exe`也就一定在同一目录；

优雅的方法就是，在可执行文件的生成后事件中把动态库拷贝到可执行文件输出目录。

## 粗暴

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 目录名字自己定
```

## 优雅

```cmake
if (WIN32)
    # 一般这条语句就够了，只拷贝dll
    add_custom_command(TARGET dynamic_lib_items_main POST_BUILD COMMAND ${CMAKE_COMMAND}
        ARGS -E copy $<TARGET_FILE:dynamic_lib_items_lib1> $<TARGET_FILE_DIR:dynamic_lib_items_main>
        COMMENT "copy dynamic lib to workdir to run")
    # 这条语句就保险一点，万一动态库还要链接一个动态库，或者动态库有自己的配置文件*.ini之类的呢
    add_custom_command(TARGET dynamic_lib_items_main POST_BUILD COMMAND ${CMAKE_COMMAND}
        ARGS -E copy $<TARGET_FILE_DIR:dynamic_lib_items_lib1> $<TARGET_FILE_DIR:dynamic_lib_items_main>
        COMMENT "copy dynamic lib dir to workdir to run")
endif ()
```

## 注意

上述解决问题的方法只是建立在整个项目使用CMake来组织的情况下，如果直接使用Visual Studio，在可执行程序的项目上添加对动态库的引用后，Visual Studio会在构建可执行程序后自动把动态库复制到可执行程序的输出目录。