# 蒟蒻云基础库-md5部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)

有问题发issues

## 状态
开发结束

## 基本信息

头文件:jry_bl_md5.h

源文件:jry_bl_md5.cpp

控制文件:暂无

类:jry_bl_md5

强制依赖项:

1.jry_bl_string

可选依赖(及相关依赖函数):

暂无

## 控制字

暂无

## 其他
```c++
jry_bl_md5(s1).get_string(); //s1是待加密字符串，使用<<承接返回值
```
测试文件叫md5

根目录 make md5

然后 exes/md5.exe
