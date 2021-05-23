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

### 变量组织结构
每一个变量都应该首先包含如下三部分。
```
	jbl_gc_define           ;
	jbl_var_ops_define      ;
	jbl_pthread_lock_define ;
```
这三部分的顺序不可颠倒或调换。

这三部分主要实现了统一的gc、var、lock封装，是保证代码正确运行的不可分割的部分。

jbl及其衍生库的变量支持引用操作，引用的使用在`jbl_gc`一节中介绍，但是在这里应当强调，由于引用的存在，函数的传入的指针可能只是引用结构的指针，在编写和测试的过程中必须对这种情况加以处理，一般的处理方式是在各组件扩容的同时进行解引用操作。

jbl封装了统一的var结构，包括一些列必要的函数，用于容器类类型操作，其具体定义在`jbl_var`一节中展示。其使用参考`jbl_ll`一节。

jbl封装了统一的锁结构，在操作时自动加锁。虽然上文已经提到了，但在这里仍需再次强调：**多线程功能已基本开发完成，但是在多线程下，加锁与浅拷贝冲突，在代码合理的情况下，有100%的几率造成死锁，固不建议开启多线程。如果一定要开启，请尽量避免在多个线程中对全局变量进行扩容、复制、引用操作。**

### jbl_gc

#### 简介

jbl_gc实现了浅拷贝，引用的操作。并为后期的自动垃圾回收预留了接口。

#### 函数接口

##### jbl_refer

输入：`void *ptr`

返回：`void *`

作用：引用ptr所指向的结构。该函数会返回一个指针，其指向一个如下定义的结构体。
```
typedef struct
{
	jbl_gc_define           ;
	jbl_var_ops_define      ;
	jbl_pthread_lock_define ;
	void * ptr;
}jbl_reference;
```
特别的，该结构体`gc`中的`ref`标志位会被置位，以此表示这是一个引用。`ptr`指针指向引用的对象。我们所说的脱引用就是递归访问每一个ptr，直到`gc`中的`ref`标志位未置位时认为解引用完成。

**特别的该函数必须传入一个二级指针，而且执行完毕后ptr也会变成引用类型**

##### jbl_derefer

输入：`void *ptr`

返回：`void *`

作用：取消引用一个变量

##### jbl_refer_pull

输入：`void *ptr`

返回：`void *`

作用：解引用

##### jbl_refer_pull_keep_father

输入：
- `void *ptr`

- `jbl_reference** ref`

返回：`void *`

作用：解引用,同时把引用的祖先放到ref中。

##### jbl_gc_init

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：0，无实际意义。

作用：初始化gc结构。

##### jbl_gc_plus

输入：`void *this`

返回：`void*`

作用：引用计数加一。

##### jbl_gc_minus

输入：`void *this`

返回：`void*`

作用：引用计数减一。

##### jbl_gc_refcnt

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：当前结构被引用了几次。

作用：当前结构被引用了几次。

##### jbl_gc_set_ref

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：无实际意义。

作用：设置引用标记。

##### jbl_gc_reset_ref

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：无实际意义。

作用：清除引用标记。

##### jbl_gc_is_ref

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：当前结构是否为引用结构。

作用：判断结构是否为引用结构。

##### jbl_gc_set_user1

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：无实际意义。

作用：设置user1标记。该标记在gc中未定义用法。

##### jbl_gc_reset_user1

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：无实际意义。

作用：清除user1标记。

##### jbl_gc_is_user1

输入：这是一个宏定义，应当直接传入指向结构的指针。

返回：当前结构是否有user1标记。

作用：判断结构是否有user1标记。

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

##### jbl_string_new

输入：无

输出：`jbl_string*`

返回：新建一个字符串，并返回一个指向该字符串的指针。

示例：

```
jbl_string *s1=jbl_string_new();
```

##### jbl_string_free

输入：`jbl_string* this`

返回：`jbl_string*`

作用：释放this指向的字符串，如果成功释放，则返回NULL。

示例：

```
jbl_string *s1=jbl_string_new();  //新建一个字符串
s1=jbl_string_free(s1);           //释放一个字符串
```

##### jbl_string_copy

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

### jbl_ll

#### 简介

jbl_ll实现了链表的操作

#### 函数接口

##### jbl_ll_new

输入：无

输出：`jbl_ll*`

返回：新建一个链表，并返回一个指向该链表的指针。

示例：

```
jbl_ll * l1=jbl_ll_new();
```

##### jbl_ll_free

输入：`jbl_ll* this`

返回：`jbl_ll*`

作用：释放this指向的链表，如果成功释放，则返回NULL。

示例：

```
jbl_ll * l1=jbl_ll_new();  //新建一个链表
l1=jbl_ll_free(l1);        //释放一个链表
```

##### jbl_ll_copy

输入：`jbl_ll* this`

返回：`jbl_ll*`

作用：复制this指向的链表并返回。

示例：

```
jbl_ll * l1=jbl_ll_new();   //新建一个链表
jbl_ll * l2=jbl_ll_copy(l1);//复制一个链表
l1=jbl_ll_free(l1);         //释放一个链表
l2=jbl_ll_free(l2);         //释放一个链表
```

##### jbl_ll_extend

输入：

- `jbl_ll* this`

- `jbl_ll_node **a`

- `jbl_ll_node **b`

- `jbl_ll **pthi`

返回：`jbl_ll*`

作用：对this所指向的链表进行扩容并返回。扩容的同时可以对节点的指针a,b进行替换，以确保这两个指针指向新的链表而非旧的链表。同时可以把解引用后的链表保存在pthi中以减少冗余的解引用操作。特别的a,b,pthi都可以为NULL。特别的this为NULL时将新建一个链表并返回。

示例：

```
jbl_ll * jbl_ll_insert(jbl_ll *this,void *var,jbl_ll_node *after)
{
    jbl_ll *thi;this=jbl_ll_extend(this,&after,NULL,&thi);//完成对this的扩容，并同步移动after指针，并将解引用后的链表保存在pthi中。
    //省略若干细节
    return this;
}
```

##### jbl_ll_foreach

输入：

- `x`

- `y`

返回：无意义

作用：这是一个宏定义，是对于for封装，以y作为枚举变量遍历x指向的链表。y会被自动定义为`jbl_ll_node`类型的指针。应当在其后按照for循环的格式继续编写代码。对于foreach，比较正常的做法是定义一个函数进行操作，但是由于C不支持匿名函数，为了减小函数命名的负担，优化代码逻辑，所以直接宏定义封装for。
**特别注意，在该循环中对x指向的链表进行删除有可能导致RE，如果要删除请使用jbl_ll_foreach_del**

##### jbl_ll_foreach_del

输入：

- `x`

- `y`

- `z`

返回：无意义

作用：这是一个宏定义，是对于for封装，以y作为枚举变量遍历x指向的链表。y会被自动定义为`jbl_ll_node`类型的指针。应当在其后按照for循环的格式继续编写代码。
需要注意的是，z同样会被声明为`jbl_ll_node`类型的指针用于支持删除操作，但用户无需理会。

##### jbl_ll_insert

输入：

- `jbl_ll* this`

- `void *var`

- `jbl_ll_node *after`

返回：`jbl_ll*`

作用：在this所指向的链表的after的后面插入var所指向的结构，特别的after是NULL时代表在头部插入,after是-1时表示在末尾插入。

示例：

```
jbl_ll * l1=jbl_ll_new();
jbl_string * v1=jbl_string_add_chars(NULL,UC"juruoyun");
l1=jbl_ll_insert(l1,v1,NULL);//链表插入
l1=jbl_ll_free(l1);
v1=jbl_var_free(v1);
```

##### jbl_ll_add

输入：

- `jbl_ll* this`

- `void *var`

返回：`jbl_ll*`

作用：在this所指向的链表的最后插入var所指向的结构。

示例：

```
jbl_ll * l1=jbl_ll_new();
jbl_string * v1=jbl_string_add_chars(NULL,UC"juruoyun");
l1=jbl_ll_insert(l1,v1,NULL);//链表插入
l1=jbl_ll_add(l1,v1);
v1=jbl_var_free(v1);
```

##### jbl_ll_merge

输入：

- `jbl_ll* this`

- `jbl_ll *that`

返回：`jbl_ll*`

作用：把that指向的链表插到this所指向的链表的后面。

示例：

```
jbl_ll * l1=jbl_ll_new();
jbl_ll * l2=jbl_ll_copy(l1);
l1=jbl_ll_merge(l1,l2);
l1=jbl_ll_free(l1);
l2=jbl_ll_free(l2);
```

##### jbl_ll_merge_ht

输入：

- `jbl_ll* this`

- `jbl_ll *that`

返回：`jbl_ll*`

作用：把that指向的哈希表插到this所指向的链表的后面。

示例：

```
jbl_ht *ht1=jbl_ht_new();
jbl_ll * l1=jbl_ll_merge_ht(NULL,ht1);
jbl_ll_view(l1);
l1=jbl_ll_free(l1);
ht1=jbl_ht_free(ht1);
```

##### jbl_ll_delete

输入：

- `jbl_ll* this`

- `jbl_ll_node *node`

返回：`jbl_ll*`

作用：删除node所指向的节点。node为NULL时删除头结点，node为-1时删除尾节点。

##### jbl_ll_delete_head

输入：`jbl_ll* this`

返回：`jbl_ll*`

作用：删除this指向的链表的头结点

##### jbl_ll_delete_tail

输入：`jbl_ll* this`

返回：`jbl_ll*`

作用：删除this指向的链表的尾结点

##### jbl_ll_get_length

输入：`jbl_ll* this`

返回：`jbl_ll_size_type`

作用：删除this指向的链表的长度

##### jbl_llv

输入：`jbl_ll_node *node`

返回：`void *`

作用：返回node所指向的节点的载荷

##### jbl_ll_swap_node

输入：
- `jbl_ll *this`
- `jbl_ll_node *a`
- `jbl_ll_node *b`

返回：`jbl_ll *`

作用：交换AB指向的节点

##### jbl_ll_space_ship

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：比较this和that。当this小于that时返回-1,this等于that时返回0，this大于that时返回1。比较时将首先比较长度，长度不同时，谁长谁大；长度相同时，将依次比较各个节点。

##### jbl_ll_if_big

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：判断this是否大于that，大于时返回1。

##### jbl_ll_if_equal

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：判断this是否等于that，等于时返回1。

##### jbl_ll_if_small

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：判断this是否小于that，小于时返回1。

##### jbl_ll_if_equal_small

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：判断this是否小于等于that，小于等于时返回1。

##### jbl_ll_if_equal_big

输入：
- `jbl_ll *this`
- `jbl_ll *that`

返回：`char`

作用：判断this是否大于等于that，大于等于时返回1。

##### jbl_ll_json_encode

输入：
- `jbl_ll* this`
- `jbl_string *out`
- `jbl_uint8 format`
- `jbl_uint32 tabs`

返回：`jbl_string*`

作用：对this指向的ll进行JSON编码，并追加在字符串out后面。format中保存了一些关于格式化的信息，例如换行,tab等，一般而言，只需要传入1(格式化)和0(不格式化)即可。tabs记录了当前应该输出多少个tab，一般传入1。

##### jbl_ll_json_put

输入：
- `jbl_ll* this`
- `jbl_stream *out`
- `jbl_uint8 format`
- `jbl_uint32 tabs`

返回：`jbl_string*`

作用：对this指向的ll进行JSON编码，并推入流out。format中保存了一些关于格式化的信息，例如换行,tab等，一般而言，只需要传入1(格式化)和0(不格式化)即可。tabs记录了当前应该输出多少个tab，一般传入1。

##### jbl_ll_view_put

输入：
- `jbl_ll* this`
- `jbl_stream *out`
- `jbl_uint8 format`
- `jbl_uint32 tabs`
- `jbl_uint32 line`
- `unsigned char * varname`
- `unsigned char * func`
- `unsigned char * file`

返回：`jbl_ll*`

作用：浏览this指向的链表并返回。**一般而言应当直接调用jbl_ll_view而非本函数**


##### jbl_ll_view

输入：`jbl_ll* this`

返回：`jbl_ll*`

作用：浏览this指向的链表并返回。









