#log moudle

## 日志系统
```
LoggerManager(singleton)

Logger(name)
   |
   |---LogFormatter(%d%T%m)
   |
LogAppender(cout, file)
```
Windows VS Code + MinGW 配置：
[CMake 入门实战](https://www.hahack.com/codes/cmake/)，需要-G参数选择编译器：`cmake .. -G "MinGW Makefiles"`。

## Windows VSCode 运行
```shell
# 配置 .vscode task.json 参见注释
Terminal -> Run Bulid Task(ctrl shift B)

cd loglr
./main.exe
```
## Windows CMake

```powershell
cd loglr
mkdir build
cd build

cmake .. # CMakeLists.txt文件所在目录 cd build 让MakeFile等文件生成在build里
make
```

终端操作如下，我已经build过了：

```powershell
PS E:\project\loglr\build> cmake ..
-- Configuring done
-- Generating done
-- Build files have been written to: E:/project/loglr/build
PS E:\project\loglr\build> make
Scanning dependencies of target loglr
[ 25%] Building CXX object CMakeFiles/loglr.dir/log.cpp.obj
[ 50%] Building CXX object CMakeFiles/loglr.dir/main.cpp.obj
[ 75%] Linking CXX executable loglr.exe
[100%] Built target loglr
PS E:\project\loglr\build>
```

