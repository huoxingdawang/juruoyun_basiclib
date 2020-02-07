# 蒟蒻云基础库-aes部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)

有问题发issues

## 状态
开发结束

## 基本信息

头文件:jry_bl_aes.h

源文件:jry_bl_aes.cpp

控制文件:暂无

类:jry_bl_aes

强制依赖项:

1.jry_bl_string

可选依赖(及相关依赖函数):

暂无

## 控制字

暂无

## 其他
```c++
jry_bl_md5(key).encode(s1); //key是秘钥,16位unsigned char *,s1是待加密字符串，使用<<承接返回值
jry_bl_md5(key).decode(s1); //key是秘钥,16位unsigned char *,s1是待解密字符串，使用<<承接返回值
```
测试文件叫aes

根目录 make aes

然后 exes/aes.exe
