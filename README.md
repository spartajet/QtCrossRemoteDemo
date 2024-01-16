## 0. 准备工作
### 0.1 WSL安装Qt5.15.2
运行代码
```bash
wget https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
chmod 777 qt-unified-linux-x64-online.run
sudo ./qt-unified-linux-x64-online.run
```
然后会出现经典QT安装目录，按照Qt安装提示即可，版本选择Qt5.15.2
> 如果出现`network error` 运行 `sudo ./qt-unified-linux-x64-online.run --mirror https://mirrors.tuna.tsinghua.edu.cn/qt`
### 0.2 WSL 安装交叉编译工具
将`atk-dlrk3568-toolchain-arm-buildroot-linux-gnueabihf-x86_64-20230921-v1.0.1.run` 文件拷贝到WSL上
然后运行指令：
```bash
sudo chmod 777 atk-dlrk3568-toolchain-arm-buildroot-linux-gnueabihf-x86_64-20230921-v1.0.1.run
sudo ./atk-dlrk3568-toolchain-arm-buildroot-linux-gnueabihf-x86_64-20230921-v1.0.1.run
```
默认安装到：`/opt/atk-dlrk356x-toolchain/` 路径中
### 0.3 WSL升级Cmake
在WSL中升级Cmake，在WSL中运行
```
sudo apt remove cmake -y
sudo apt update
sudo apt install cmake
```
这时，你会惊奇的发现安装的还是camke 3.16.3，这是ubuntu20.04支持的cmake最高版本就是3.16.3。怎么解决这个问题呢？可以修改CMakeList.txt文件第一行
```camke
cmake_minimum_required(VERSION 3.16)
```
支持详情如下：
```
Ubuntu 16.04 ships with cmake-3.5.1
Ubuntu 17.10 ships with cmake-3.9.1
Ubuntu 18.04 ships with cmake-3.10.2
Ubuntu 20.04 ships with cmake-3.16.3
Ubuntu 21.04 ships with cmake-3.18.4
```
### 0.4 WSL 安装GDB
如果在Debugger中出现找不到WSL GDB错误时，请在WSL中安装GDB，运行
```shell
sudo apt install gdb
```
### 0.5 WSL安装libgl1-mesa-dev
```
sudo apt-get install libgl1-mesa-dev
```
## 1. 创建Qt项目
如图所示，创建一个`QtRemoteDemo`项目
![](https://file.spartajet.com/202401122142620.png)
然后设置本地`ToolSet`
![](https://file.spartajet.com/202401122143530.png)
运行程序，确保Cmake配置正确
![](https://file.spartajet.com/202401122144859.png)
如图，程序是可以运行的。
## 2. 配置Clion WSL 编译
配置WSL 工具链
![](https://file.spartajet.com/202401122145022.png)
配置如图所示。
![](https://file.spartajet.com/202401122151916.png)
这时，Cmake会报错：
![](https://file.spartajet.com/202401122222791.png)

设置WSL为默认工具链
![](https://file.spartajet.com/202401122152897.png)
Clion右上角 `Add Configuration`,如图所示
![](https://file.spartajet.com/202401122156033.png)
配置结果如图所示
![](https://file.spartajet.com/202401122259874.png)
这时，即可运行程序，WSL是可以显示GUI窗体的，如图所示
![](https://file.spartajet.com/202401122317753.png)

## 3. 配置Clion WSL 交叉编译
>嵌入式开发中，交叉编译是必须的，。如果仅开发与硬件无关的GUI，还可以暂时无需交叉编译器。但RK3568有很多硬件外设，所以还是要配置交叉编译的

新增一个Tool Chain 如下图所示，命名为`WSL-Cross`
![](https://file.spartajet.com/202401122326331.png)
设置`ToolSet` 为`WSL-Cross`，如下图所示
![](https://file.spartajet.com/202401122328047.png)




## 4. 配置RK3568 部署调试

新增Remote GDB Server，如图所示
![](https://file.spartajet.com/202401130047571.png)
然后点击右上角Debug按钮，得到如下错误
![](https://file.spartajet.com/202401130048580.png)
解决方法：配置环境变量
![](https://file.spartajet.com/202401130058443.png)
```
QT_QPA_PLATFORM=wayland
XDG_RUNTIME_DIR=/var/run/
```

## 5. Cmake文件
```cmake
cmake_minimum_required(VERSION 3.16)
project(QtRemote)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH  "/opt/atk-dlrk356x-toolchain/aarch64-buildroot-linux-gnu/sysroot/usr/lib/cmake/")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        PATHS "/opt/atk-dlrk356x-toolchain/aarch64-buildroot-linux-gnu/sysroot/usr/lib/"
)

add_executable(QtRemote main.cpp)
target_link_libraries(QtRemote
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

```

 [Github Demo](https://github.com/spartajet/QtCrossRemoteDemo) 



