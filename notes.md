## 项目的一些说明
一个C++项目来说
1. C++场景下的使用 CLi 命令行
2. Python的封装 C_Api的问题



> 为什么Loss Metric等类的Calculate函数不返回结果?
>
因为需要做积累，多个线程的操作、多个文件数据源的积累，
结果统一由GetValue返回结果



### 项目的结构
本项目只有唯一的入口点 Entry Point
Solver
整体的流程是：
Solver-> Trainer   -> Loss -> Score
Solver-> Predictor -> Loss -> Score

Loss模块针对数据集操作 DMatrix *data
Score模块针对单个样本操作 SparseRow *row 

### 开发规范
尽量遵守谷歌C++开发规范
 
### 开发的偏好
* 类实例作为其他类的成员变量时使用指针方式，
作为函数参数传递时则根据情况变动，
如果该参数要求不能为空，则尽量使用引用方式，因为可以避免非空判断;
如果可以要求为空，则使用指针方式。

* 所有的类都通过Initialize函数进行成员变量的初始化 
而不是构造函数

* 所有的Initialize()函数都需要CHECK检测参数的合法性
