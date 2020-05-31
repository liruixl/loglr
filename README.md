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

