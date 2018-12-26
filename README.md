# Upper-Computer

## Introduction
- `master`: Latest stable version of the new type of hardware(v2).
- `dev_*`: Developing version aiming to add * function.
- `fix_*`: Developing version aiming to fix * issue.
- `2.*.*`: History version of the new type of hardware(v2).
- `1.*.*`: History version of the old type of hardware(v1).

## Todo
- [x] socket -> Websocket
- [ ] add 1.0.0
- [ ] fix stability issues
- [ ] MERGE
- [ ] Test
- [ ] string matching -> xml lib

## How to build?

1. 安装开发环境：Visual Studio 2017（2015/2010应该也是可以的，只是后面的版本对应需要另外查询）
2. 下载[C++ Boost Lib](https://sourceforge.net/projects/boost/files/boost-binaries/)提供的windows编译版本，注意需要与目标操作系统和VS编译器版本配套，VS2017对应的编译器版本为msvc14.1，目标系统是32位，因此要下载的是1.68.0（boost版本不重要，别太老就行）文件夹下的boost_1_68_0-msvc-14.1-32.exe。下载完成后运行安装即可。
3. 下载[Websocketpp Lib](https://github.com/zaphoyd/websocketpp/releases)的源代码，我使用的是0.8.1版本，下载完成后解压即可。
4. 用VS打开UpperComputer.sln，一路确定，成功打开后，在右侧解决方案资源管理器中，右击UpperComputer，选择属性。
5. 在配置属性--->常规中，选择平台工具集为Visual Studio 2017 - Windows XP (v141_xp)，否则最终编译的程序无法在XP系统上运行。
6. 在配置属性--->VC++目录中，在包含目录中添加以下路径：boost安装目录\boost_1_68_0_32，websocketpp解压目录\websocketpp-0.8.1。并在库目录中添加以下依赖：boost安装目录\boost_1_68_0_32\lib32-msvc-14.1。
7. 完成上述操作后即可编译运行。