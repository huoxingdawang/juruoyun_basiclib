# 蒟蒻云基础库
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)

有问题发issues,欢迎PR
## 简介

一套低性能C语言库，是作者阅读《php7底层设计与源码实现》时的仿制之作。

对于C语言的一些功能进行了封装。

## 支持平台

- linux(gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)),(re2c 1.3)

- windows(gcc version 8.1.0 (x86_64-posix-seh-rev0, Built by MinGW-W64 project)),(re2c 0.9.4)

- macos(Apple clang version 12.0.0 (clang-1200.0.32.27)),(re2c 2.0.3)

*特别需要注意，由于windows下re2c支持有问题，windows平台下可能无法正常构建*

### 目前已经包含

- AES128CBC，AES128ECB 加解密，支持AESNI指令集加速

- BASE64编解码

- bitset位操作器

- 外部调用shell/cmd命令并返回结果

- 大小端字节序转换

- 异常处理

- 文件操作

- 垃圾回收（暂不支持处理循环引用问题）

- 哈希表

- JSON编解码

- 链表

- log记录

- 内存管理

- MD5加密

- 随机数

- SHA1加密

- 流式处理器

- 字符串

- UTF-8 GB2312 Unicode互转与输出自动更改编码

### 正在开发项目

多线程支持

**多线程功能已基本开发完成，但是在多线程下，加锁与浅拷贝冲突，在代码合理的情况下，有100%的几率造成死锁，固不建议开启多线程。如果一定要开启，请尽量避免在多个线程中对全局变量进行扩容、复制、引用操作。**

时间格式化

## 环境搭建指北

需要GCC，RE2C，MAKE

初次编译请先运行make init创建目录

然后make

可以单独make 组建列如make string来单独编译string的样例

所有的测试程序会在exes/目录下

## 使用手册

### 代码规范

变量与函数命名均使用全小写下划线命名方式。

宏定义，常量使用全大写下划线命名方式。

文件名同样使用全小写下划线命名方式。

对于一般的函数，应当遵循`项目缩写_功能模块_执行操作`的方式命名，比如函数`jbl_string_new`说明该函数属于juruoyun basic lib项目，分属string功能模块，执行new操作。

下面对变量的基本操作作出规范

| 操作 | 解释 | 备注 |
| :-----| ----: | :----: |
| start | 启动功能模块 | 完成对本功能模块所需全局变量、内存的初始化 |
| stop | 停止功能模块 | 完成对本功能模块所需全局变量、内存的释放 |
| new | 新建变量 | 完成对于内存的申请和自身初始化 |
| free | 释放变量 | 完成对于变量所占内存的释放 |
| copy | 复制变量 | 产生一个变量的副本 |
| extend | 扩容变量 | 对于容器类变量，确保空间足够，对于在copy中实现浅拷贝的变量，此时需要完成写时复制 |

对于一般测全局变量，应当遵循`项目缩写_功能模块_执行操作`的方式命名。

对于有static修饰的全局变量和函数，可以省略`项目缩写_功能模块`只保留`执行操作`。

对于局部变量，可以不遵循命名规范，但应当表意清晰。

对于大括号，应当另起一行书写，除非以下几种情况。

1. 多个if else嵌套或者switch case语句，每一个分支内代码长度较短，功能相近的，可以不写大括号直接在一行内完成。例如下面的代码，被认为是符合格式的。
```
[^]			{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_UNDEFINED;}	
[\x00]		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_END;}	
"%d"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_INT;}	
"%f"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_DOUBLE;}
"%s"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_CHARS;}
"%c"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_CHAR;}
"%X"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_HEX;}
"%errstr"	{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_ERRSTR;}
"%v"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_VAR;}
"%j"		{if(addr)*addr=YYCURSOR;return JBL_SCANNER_KEY_JSON;}
```

### jbl_string

#### 简介

jbl_string实现了字符串的操作

#### 函数接口

##### jbl_string_start

输入：无

返回：无

作用：启动string 


##### jbl_string_stop

输入：无

返回：无

作用：停止string 

#### jbl_string_new

输入：无

输出：`jbl_string*`

返回：新建一个字符串，并返回一个指向该字符串的指针。

示例：

```
jbl_string *s1=jbl_string_new();
```

#### jbl_string_free

输入：`jbl_string* this`

返回：`jbl_string*`

作用：释放this指向字符串，如果成功释放，则返回NULL。

示例：

```
jbl_string *s1=jbl_string_new();  //新建一个字符串
s1=jbl_string_free(s1);           //释放一个字符串
```

#### jbl_string_copy

输入：`jbl_string* this`

返回：`jbl_string*`

作用：复制this指向的字符串并返回。

示例：

```
jbl_string *s1=jbl_string_new();      //新建一个字符串
jbl_string *s2=s2=jbl_string_copy(s1);//复制一个字符串
s1=jbl_string_free(s1);               //释放一个字符串
s2=jbl_string_free(s2);               //释放一个字符串
```
									//清空一个字符串