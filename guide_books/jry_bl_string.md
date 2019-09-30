# 蒟蒻云基础库-字符串部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)

有问题发issues

## 状态
正在开发


## 基本信息

头文件:jry_bl_string.h

源文件:jry_bl_string.cpp

控制文件:jry_bl_string_config.h

类:jry_bl_string

强制依赖项:

1.cmath(于近期撤销)

2.jry_bl_exception

3.jry_bl_malloc

可选依赖(及相关依赖函数):

1.stdio(view)

2.iostream(<</>>数据流)

## 控制字

1.JRY_BL_STRING_BASIC_LENGTH 控制一次扩展内存最小步进长度

2.JRY_BL_STRING_SIZE_TYPE 控制存储长度的变量的类型

3.JRY_BL_STRING_USE_IOSTREAM 控制对于iostream的依赖项(设为0则不能向ostream中写数据，也不能从istream读数据)

4.JRY_BL_STRING_USE_CSTDIO 控制对于cstdio的依赖(设为0不能使用view函数)

## 注意事项

1.在使用加法，to_json函数时请务必使用<<操作符进行赋值，否则会发生内存泄露！

正确的示范

```c++
jry_bl_string s1;
s1<<'a'+"123123123"+123;
```

错误示范

```c++
jry_bl_string s1;
s1='a'+"123123123"+123;//会发生内存泄露
```

## example

在examples/string.cpp中

在工程目录中执行 make string

然后运行 exes/string.cpp查看输出

## 杂项

### 重载的运算符

1.[]

2.+=

3.=

4.+

5.<<(输出)

6.>>(输入)

7.<<（浅拷贝）

8.>>（浅拷贝）

### 函数

1.void view(FILE * file); 查看细节(依赖cstdio)

1.void free(); 释放空间

3.void parse(); 压缩空间至恰好装下内容

4.void extend(JRY_BL_STRING_SIZE_TYPE sizee); 扩展空间至sizee大小

5.long long get_int(); 从第0位开始获取一个整数

6.long long get_int(JRY_BL_STRING_SIZE_TYPE start); 从start位开始获取一个整数

7.long double get_float(); 从第0位开始获取一个浮点数

8.long double get_float(JRY_BL_STRING_SIZE_TYPE start); 从start位开始获取一个浮点数

9.bool get_is_light_copy(); 查看是不是浅拷贝产物

10.jry_bl_string to_json(); 转化成JSON字符串(请用<<承接)

11.void from_json(jry_bl_string &in); 从in的第0位开始解码JSON至字符串类型

12.void from_json(jry_bl_string &in,JRY_BL_STRING_SIZE_TYPE start); 从in的start位开始解码JSON至字符串类型

13.JRY_BL_STRING_SIZE_TYPE get_length(); 获取字符串长度