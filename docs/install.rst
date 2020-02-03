
安装指南
===============

通过Pip安装
-----------
暂时不支持


从源代码安装
--------------

Linux 下安装
--------------

.. code-block:: shell

    sudo apt-get install git
    sudo apt-get install cmake
    git clone https://github.com/naihaishy/FMLearn.git
    cd FMLearn
    mkdir build && cd build
    cmake ..
    make && make install

Windows 下安装
--------------

安装Visual Studio
^^^^^^^^^^^^^^^^^^^^^^
如果你的 Windows 系统已经安装过 Visual Studio，你可以跳过这一步。

从 https://visualstudio.microsoft.com/downloads/ 下载你所需要的 Visual studio

安装Cmake
^^^^^^^^^
如果你的系统已经安装了 CMake，你可以跳过这一步

从这里 https://cmake.org/download/ 下载最新版本 (至少 v3.10) CMake。请确保安装 CMake 后将其路径正确添加到你的系统路径。

编译
^^^^

下载源代码执行 build.bat

注意 如果您的编译器不是 Visual Studio 15 2017， 则定制修改build.bat 即可

执行完会打开VS项目

构建ALL_BUILD

构建INSTALL

结果全部在results\目录下, 执行run_test.bat执行测试




