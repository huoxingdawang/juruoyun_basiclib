# 蒟蒻云基础库-异常部分用户手册
![](http://www.juruoyun.top/jry_wb/jry_wb_netdisk/jry_nd_do_file.php?action=open&share_id=4&file_id=15)

有问题发issues

## 状态
开发结束

## 基本信息

头文件:jry_bl_exception.h

源文件:jry_bl_exception.cpp

控制文件:暂无

类:暂无

强制依赖项:

1. iostream

可选依赖(及相关依赖函数):

暂无

## 控制字

暂无

##其他

这玩意比较简单

有一个宏定义jry_bl_exception(x)

x中填字符串

会调用函数void _jry_bl_exception(const char * file,int line,const char* x);

参数都是字面意思。。。。

可以重写