Windows下，不管是使用VS Code进行本地调试还是远程调试，调试有输入的程序都不会出现输入窗口。

先给解决方案。打开`setting.json`，添加如下代码：

```cmake
    "cmake.debugConfig": {
        "console": "integratedTerminal"
    }
```

其实这里使用`"console": "externalConsole"`对于本地调试来说也是没有问题的，但是远程调试是出不来的。

点击下方状态栏的**小蜘蛛**或者直接`Ctrl + F5`调试。

即可解决CMakeTools调试时没有输入窗口的问题。这才是最优雅的方法。之前没有认真看文档[vscode-cmake-tools/docs/debug-launch.md](https://github.com/microsoft/vscode-cmake-tools/blob/develop/docs/debug-launch.md)，所以曲线救国用了另一种方法：[CMake适配VS Code调试有标准输入的程序](https://blog.csdn.net/FlushHip/article/details/114677718)。

通过查看代码[vscode-cmake-tools/src/debugger.ts](https://github.com/microsoft/vscode-cmake-tools/blob/develop/src/debugger.ts)，其实，CMakeTools是自动根据工具集来生成调试的配置`launch.json`来调试的。

如果对CMakeTools的自动生成的`launch.json`还有一些特殊的要求，而这些特殊的要求不能通过`cmake.debugConfig`来解决，那么我们就需要去定制自己的`launch.json`。

从代码中可以看出，配置`launch.json`调试和CMakeTools有关的参数有如下：

- `program`：程序路径，这里可以用值`${command:cmake.launchTargetPath}`来联动；
- `cwd`：工作路径，这里可以用值`{command:cmake.launchTargetDirectory}`来联动。

更多信息请参考：[Configure CMake Tools settings](https://github.com/microsoft/vscode-cmake-tools/blob/develop/docs/cmake-settings.md)。

这里还要多说一句，如果是使用`launch.json`Windows上远程调试Linux程序（使用CMakeTools生成），还需要在`launch.json`添加如下才能出现输入窗口：

```json
            "externalConsole": false,
            "avoidWindowsConsoleRedirection": false,
```

