# 蒟蒻云基础库-base64部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)
有问题发issues

## 状态
开发结束

## 基本信息

头文件:jry_bl_base64.h

源文件:jry_bl_base64.cpp

控制文件:暂无

类:暂无

强制依赖项:

1.jry_bl_string

可选依赖(及相关依赖函数):

暂无

## 控制字

暂无

##其他
```c++
jry_bl_string jry_bl_base64_encode(jry_bl_string &a) //加密一个字符串，使用<<承接
jry_bl_string jry_bl_base64_decode(jry_bl_string &a) //解密一个字符串，使用<<承接
```
测试文件叫base64

根目录 make base64

然后 exes/base64.exe
